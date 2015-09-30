#ifndef DEVICE_H_
#define DEVICE_H_

#include <string>
#include <iostream>
#include <vector>

class Device {
public:
	Device(std::string manufacturer, std::string product,
			unsigned int productID, unsigned int vendorID,
			unsigned int busnumber, std::vector<int> portnumber,
			std::string ttypath);
	~Device();

	void setManufacturer(char* manufacturer) { manufacturer_ = std::string(manufacturer); }
	void setManufacturer(std::string manufacturer) { manufacturer_ = manufacturer; }
	std::string getManufacturer() const { return manufacturer_; }

	void setProduct(char* product) { product_ = std::string(product); }
	void setProdcut (std::string product) { product_ = product; }
	std::string getProduct() const { return product_; }

	void setSerialDevicePath(char* serialDevicePath) { serial_device_path_ = std::string(serialDevicePath); }
	void setSerialDevicePath(std::string serialDevicePath) { serial_device_path_ = serialDevicePath; }
	std::string getSerialDevicePath() const { return serial_device_path_; }

	void setProductId(unsigned int productId) {	product_ID_ = productId; }
	unsigned int getProductId() const {	return product_ID_; }

	void setVendorId(unsigned int vendorId) { vendor_ID_ = vendorId; }
	unsigned int getVendorId() const { return vendor_ID_; }

	void setBusNumber(unsigned int busNumber) { bus_number_ = busNumber; }
	unsigned int getBusNumber() const { return bus_number_; }

	void setPortNumber(std::vector<int> portNumber) { port_number_ = portNumber; }
	std::vector<int> getPortNumber() const { return port_number_; }

	std::string getPortNumberAsString() const;

	friend std::ostream& operator<<(std::ostream& stream, const Device& dev) {
		stream << "VendorID: " << dev.vendor_ID_
				<< " ||| ProductID: " << dev.product_ID_
				<< " ||| Manufacturer: " << dev.manufacturer_
				<< " ||| Product: " << dev.product_
				<< " ||| Bus: " << dev.bus_number_
				<< " ||| Port: " << dev.getPortNumberAsString()
				<< " ||| Path: " << dev.serial_device_path_ << std::endl;
		return stream;
	}

private:
	std::string manufacturer_;
	std::string product_;
	std::string serial_device_path_;

	unsigned int product_ID_;
	unsigned int vendor_ID_;
	unsigned int bus_number_;
	std::vector<int> port_number_;
};

#endif /* DEVICE_H_ */
