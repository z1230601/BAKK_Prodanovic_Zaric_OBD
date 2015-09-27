#ifndef DEVICE_H_
#define DEVICE_H_

#include <string.h>

class Device {
public:
	Device(std::string manufacturer, std::string product, unsigned int productID, unsigned int vendorID );
	~Device();

	void setManufacturer(char* manufacturer) { manufacturer_ = std::string(manufacturer); }
	void setManufacturer(std::string manufacturer) { manufacturer_ = manufacturer; }
	std::string getManufacturerIdx() const { return manufacturer_; }

	void setProduct(char* product) { product_ = std::string(product); }
	void setProdcut (std::string product) { product_ = product }
	std::string getProduct() const { return product_; }

	void setProductId(unsigned int productId) {	product_ID_ = productId; }
	unsigned int getProductId() const {	return product_ID_; }

	void setVendorId(unsigned int vendorId) { vendor_ID_ = vendorId; }
	unsigned int getVendorId() const { return vendor_ID_; }

private:
	std::string manufacturer_;
	std::string product_;
	unsigned int product_ID_;
	unsigned int vendor_ID_;
};

#endif /* DEVICE_H_ */
