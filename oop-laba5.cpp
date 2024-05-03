#include <iostream>
#include <string>
#include <vector>

namespace {
	enum class Material { Plastic, Metal, Glass };

	std::ostream& operator<<(std::ostream& os, const Material& material) {
		static const std::vector<std::string> materials = { "Plastic", "Metal", "Glass" };
		return os << materials[static_cast<int>(material)];
	}

	std::istream& operator>>(std::istream& is, Material& material) {
		int userChoice;
		is >> userChoice;
		material = static_cast<Material>(userChoice);
		return is;
	}
}

class MeasurementDevice {
protected:
	std::string name;
	std::string unit;
	double minValue;
	double maxValue;
	Material material;
	bool isDeviceActiveForMeasurement;

public:
	MeasurementDevice(const std::string& name, const std::string& unit, double minValue, double maxValue, Material material)
		: name(name), unit(unit), minValue(minValue), maxValue(maxValue), material(material), isDeviceActiveForMeasurement(false) {}

	virtual void startMeasuring() {
		if (!isDeviceActiveForMeasurement) {
			std::cout << "\nStart of measurement" << std::endl;
			isDeviceActiveForMeasurement = true;
		}
	}

	virtual void stopMeasuring() {
		if (isDeviceActiveForMeasurement) {
			std::cout << "End of measurement\n" << std::endl;
			isDeviceActiveForMeasurement = false;
		}
	}

	virtual void print() const {
		std::cout << "============" << std::endl;
		std::cout << "Name: " << name << std::endl;
		std::cout << "Unit: " << unit << std::endl;
		std::cout << "Min Value: " << minValue << std::endl;
		std::cout << "Max Value: " << maxValue << std::endl;
		std::cout << "Material: " << material << std::endl;
		std::cout << "============" << std::endl;
	}

	void setName() {
		std::cout << "Enter new device name: ";
		std::getline(std::cin >> std::ws, name);
	}

	void setUnit() {
		std::cout << "Enter new unit: ";
		std::getline(std::cin >> std::ws, unit);
	}

	void setMinValue() {
		std::cout << "Enter new min value: ";
		std::cin >> minValue;
	}

	void setMaxValue() {
		std::cout << "Enter new max value: ";
		std::cin >> maxValue;
	}

	void setMaterial() {
		int materialChoice;
		do {
			std::cout << "Enter material (1 for Plastic, 2 for Metal, 3 for Glass): ";
			std::cin >> materialChoice;
			if (materialChoice >= 1 && materialChoice <= 3) {
				material = static_cast<Material>(materialChoice - 1);
				break;
			}
			else {
				std::cout << "Invalid choice. Please try again." << std::endl;
			}
		} while (true);
	}
};

class TemperatureMeasurementDevice : public MeasurementDevice {
private:
	double currentTemperature;
	enum class TemperatureScale { Celsius, Fahrenheit, Kelvin };
	TemperatureScale temperatureScale;

public:
	TemperatureMeasurementDevice(const std::string& name, const std::string& unit, double minValue, double maxValue, Material material)
		: MeasurementDevice(name, unit, minValue, maxValue, material) {
		int userChoice;
		do {
			std::cout << "Enter temperature scale (1 for Celsius, 2 for Fahrenheit, 3 for Kelvin): ";
			std::cin >> userChoice;
			if (userChoice >= 1 && userChoice <= 3) {
				temperatureScale = static_cast<TemperatureScale>(userChoice - 1);
				break;
			}
			else {
				std::cout << "Invalid choice. Please try again." << std::endl;
			}
		} while (true);
	}

	void startMeasuring() override {
		MeasurementDevice::startMeasuring();
		std::cout << "Temperature measurement started" << std::endl;
	}

	void stopMeasuring() override {
		MeasurementDevice::stopMeasuring();
		std::cout << "Temperature measurement stopped" << std::endl;
	}

	void print() const override {
		MeasurementDevice::print();
		printTemperature();
	}

	void setCurrentTemperature() {
		if (isDeviceActiveForMeasurement) {
			double rangeTemp;

			do {
				std::cout << "Enter current temperature (" << minValue << " - " << maxValue << "): ";
				std::cin >> rangeTemp;

				if (rangeTemp <minValue || rangeTemp > maxValue) {
					std::cout << "Temperature out of range. Please enter a value between " << minValue << " and " << maxValue << "." << std::endl;
				}
				else {
					currentTemperature = rangeTemp;
					break;
				}
			} while (true);
		}
		else {
			std::cout << "Device is not ACTIVE!!!" << std::endl;
		}
	}

	void printTemperature() const {
		std::string scale;

		switch (temperatureScale) {
		case TemperatureScale::Celsius:
			scale = "Celsius";
			break;
		case TemperatureScale::Fahrenheit:
			scale = "Fahrenheit";
			break;
		case TemperatureScale::Kelvin:
			scale = "Kelvin";
			break;
		default:
			scale = "Celsius";
			break;
		}

		std::cout << "Current Temperature: " << currentTemperature << " " << scale << std::endl;
	}

	void setTemperatureScale() {
		int userChoice;
		do {
			std::cout << "Enter temperature scale (1 for Celsius, 2 for Fahrenheit, 3 for Kelvin): ";
			std::cin >> userChoice;
			if (userChoice >= 1 && userChoice <= 3) {
				temperatureScale = static_cast<TemperatureScale>(userChoice - 1);
				break;
			}
			else {
				std::cout << "Invalid choice. Please try again." << std::endl;
			}
		} while (true);
	}
};

int main() {
	std::string name, unit;
	double minValue, maxValue;
	Material material;

	std::cout << "Enter device name: ";
	std::getline(std::cin, name);
	std::cout << "Enter unit: ";
	std::getline(std::cin, unit);
	std::cout << "Enter min value: ";
	std::cin >> minValue;
	std::cout << "Enter max value: ";
	std::cin >> maxValue;
	int materialChoice;
	do {
		std::cout << "Enter material (1 for Plastic, 2 for Metal, 3 for Glass): ";
		std::cin >> materialChoice;
		if (materialChoice >= 1 && materialChoice <= 3) {
			material = static_cast<Material>(materialChoice - 1);
			break;
		}
		else {
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	} while (true);

	TemperatureMeasurementDevice device(name, unit, minValue, maxValue, material);

	int option;
	std::cout << "\nChoose an option:\n1. Start measuring\n2. Stop measuring\n3. Print device info\n4. Set temperature\n5. Print temperature\n6. Change device attributes\n0. Exit\nEnter option: ";

	do {
		std::cin >> option;

		switch (option) {
		case 1:
			device.startMeasuring();
			break;
		case 2:
			device.stopMeasuring();
			break;
		case 3:
			device.print();
			break;
		case 4:
			device.setCurrentTemperature();
			break;
		case 5:
			device.printTemperature();
			break;
		case 6: {
			int attributeOption;
			bool exitAttributeMenu = false;
			std::cout << "Choose an attribute to change:\n1. Name\n2. Unit\n3. Min Value\n4. Max Value\n5. Material\n6. Temperature Scale\n0. Exit\nEnter option: ";

			while (!exitAttributeMenu) {
				std::cin >> attributeOption;

				switch (attributeOption) {
				case 1:
					device.setName();
					break;
				case 2:
					device.setUnit();
					break;
				case 3:
					device.setMinValue();
					break;
				case 4:
					device.setMaxValue();
					break;
				case 5:
					device.setMaterial();
					break;
				case 6:
					device.setTemperatureScale();
					break;
				case 0:
					exitAttributeMenu = true;
					break;
				default:
					std::cout << "Invalid option. Please try again." << std::endl;
					break;
				}
			}

			break;
		}
		case 0:
			std::cout << "Exiting program." << std::endl;
			break;
		default:
			std::cout << "Invalid option. Please try again." << std::endl;
			break;
		}
	} while (option != 0);

	return 0;
}