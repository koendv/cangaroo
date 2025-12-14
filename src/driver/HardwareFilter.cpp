#include "HardwareFilter.h"
#include "CanDriver.h"
#include "CanFilter/canfilter.hpp"
#include "CanFilter/canfilter_bxcan.hpp"
#include "CanFilter/canfilter_fdcan.hpp"
#include "CanFilter/canfilter_usb.hpp"
#include "CanFilter/usb_info.hpp"
#include "core/Backend.h"

bool setHardwareFilter(CanInterface *intf, QString filter_def) {

  log_info(QString("interface: %1, filter: %2").arg(intf->getName(),filter_def));

  QString driver_name = intf->getDriver()->getName();
  if (driver_name != "SocketCAN") {
    log_error("hwfilter: not SocketCAN");
    return false;
  }

  QString if_name = intf->getName();
  uint16_t vendor_id, product_id;
  canfilter_usb usb_device;
  canfilter_hardware_t hw_filter;
  std::string serial;
  std::unique_ptr<canfilter> filter;

  if (!getUsbInfoFromDeviceName(if_name.toStdString(), vendor_id, product_id, serial)) {
    log_error("hwfilter: interface not found");
    return false;
  }

  if (!usb_device.open(vendor_id, product_id, serial)) {
    log_error("hwfilter: could not find backend for interface");
    return false;
  }

  if (!usb_device.hasHardwareFilter()) {
    log_error("hwfilter: controller does not have hardware filter ");
    return false;
  }

  hw_filter = (canfilter_hardware_t)usb_device.getFilterInfo();

  switch (hw_filter) {
  case CANFILTER_DEV_BXCAN_F0:
    filter.reset(new canfilter_bxcan_f0());
    log_info("Using bxCAN (F0/F1/F3) with 14 filter banks");
    break;
  case CANFILTER_DEV_BXCAN_F4:
    filter.reset(new canfilter_bxcan_f4());
    log_info("Using bxCAN (F4/F7) with 28 filter banks");
    break;
  case CANFILTER_DEV_FDCAN_G0:
    filter.reset(new canfilter_fdcan_g0());
    log_info("Using FDCAN (G0) with 28 standard, 8 extended filters");
    break;
  case CANFILTER_DEV_FDCAN_H7:
    filter.reset(new canfilter_fdcan_h7());
    log_info("Using FDCAN (H7) with 128 standard, 64 extended filters");
    break;
  case CANFILTER_DEV_NONE:
  default:
    log_error("hwfilter: invalid output mode");
    return false;
    break;
  }

  filter->begin();
  if (!filter->parse(filter_def.toStdString())) {
    log_error("hwfilter: filter syntax error");
    return false;
  }
  filter->end();

  if (!usb_device.programFilter(filter->get_hw_config(), filter->get_hw_size())) {
    log_error("hwfilter: filter fail");
    return false;
  }

  log_info("filter success");

  return true;
}
