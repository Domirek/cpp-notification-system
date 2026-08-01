#include <iostream>
#include <string>
#include <vector>
#include <memory>




class INotifier {
	public:
		virtual ~INotifier() = default; //виртуальный деструктор в интерфейсе позволяет создавать автоматические деструкторы в дочерних классах

		virtual void send(const std::string& recipient, const std::string& message) const = 0;
		virtual bool IsAvailable() const { return true; };
};



class EmailNotifier : public INotifier {
	std::string smtp;

	public:
		explicit EmailNotifier(std::string smtp_) { smtp = smtp_; } //здесь и далее: explicint исключает неявное преобразование при передачи переменной 

		void send(const std::string& recipient, const std::string& message) const override { //override переопределение функции из интерфейса
			std::cout << "[EMAIL] to: " << recipient << " | SMTP: " << smtp << " | Msg: " << message << std::endl;
		};
};

class SmsNotifier : public INotifier {
	std::string provider;

	public:
		explicit SmsNotifier(std::string provider_) { provider = provider_; }

		void send(const std::string& recipient, const std::string& message) const override {
			std::cout << "[SMS] to: " << recipient << " | Provider: " << provider << " | Msg: " << message << std::endl;
		};
};

class PushlNotifier : public INotifier {
	std::string app;

	public:
		explicit PushlNotifier(std::string app_) { app = app_; }

		void send(const std::string& recipient, const std::string& message) const override {
			std::cout << "[NOTIFICATION] to: " << recipient << " | App: " << app << " | Msg: " << message << std::endl;
		};
};



void NotifyUser(const INotifier &notifier, const std::string& recipient, const std::string& message) {
	notifier.send(recipient, message);
	std::cout << "--- Notification sent---\n";
};





int main() {
	std::vector<std::unique_ptr<INotifier>> notifiers; //unique_ptr автоматически очистит память как только обьект выйдет из области видимости
	notifiers.push_back(std::make_unique<EmailNotifier>("smtp.gmail.com")); //make_unique создание обьекта без утечки памяти
	notifiers.push_back(std::make_unique<SmsNotifier>("MTS"));

	for (size_t i = 0; i < notifiers.size(); ++i) {
		std::string recipient = (i == 0) ? "Oleg@gmail.com" : "+79123456789";
		std::string message = "Hello world! Meet me at lunch time\n";
		NotifyUser(*notifiers[i], recipient, message);
	}

	return 0;
}
