// Обчислення значень функції на заданому проміжку

#include <iostream> // введення cin і виведення cout
#include <iomanip>  // оформлення таблиці
#include <sstream>  // перевірка введеного тексту
#include <string>   // зберігання тексту
#include <cmath>    // функції floor та isfinite
#include <cstdlib>  // завершення програми через exit

#ifdef _WIN32
#include <windows.h> // налаштування консолі windows
#endif

using namespace std; // дозволяє писати cout, cin і string коротше

int language = 1; // зберігає номер мови

// вибирає український або англійський текст
string message(string uk, string en) {
	return language == 1 ? uk : en;
}

// виводить заголовок між розділювачами
void showTitle(string uk, string en) {
	cout << "\n============================================================\n";
	cout << "  " << message(uk, en) << '\n';
	cout << "============================================================\n";
}

// показує формулу та пояснює позначення
void showFormula() {
	cout << message("  При x < -3:\n", "  For x < -3:\n");
	cout << "  y = SUM[i=1..n] ((i + x)^2 / (2*i))\n\n";

	cout << message("  При x >= -3:\n", "  For x >= -3:\n");
	cout << "  y = PROD[j=1..n-1] (SUM[i=2..n+1] (i + i/j - j)^2)\n\n";

	cout << message(
		"  SUM - сума, PROD - добуток, ^2 - квадрат\n",
		"  SUM - sum, PROD - product, ^2 - square\n");
}

// чекає натискання enter
void waitForEnter() {
	cout << message(
		"\nНатисніть Enter, щоб повернутися до меню...",
		"\nPress Enter to return to the menu...");

	string line;
	if (!getline(cin, line)) exit(0);
	cout << '\n';
}

// повторює запит, поки користувач не введе число
double readNumber(string prompt) {
	string line;   // увесь введений текст
	double number; // число з цього тексту
	char extra;    // зайвий символ після числа

	while (true) {
		cout << prompt;
		if (!getline(cin, line)) exit(0);

		istringstream input(line);

		// перевіряє число, відсутність зайвих символів і скінченність
		if ((input >> number) && !(input >> extra) && isfinite(number))
			return number;

		cout << message(
			"[!] Введіть будь ласка число\n\n",
			"[!] Please enter a number\n\n");
	}
}

// обчислює y за формулою
double calculate(double x, int n) {
	double y = 0; // початкове значення суми

	if (x < -3) {
		// перебирає i від 1 до n
		for (int i = 1; i <= n; i++)
			y += (i + x) * (i + x) / (2.0 * i); // додає доданок до y
	}
	else {
		y = 1; // початкове значення добутку

		// перебирає j від 1 до n - 1
		for (int j = 1; j < n; j++) {
			double sum = 0; // нова сума для кожного j

			// перебирає i від 2 до n + 1
			for (int i = 2; i <= n + 1; i++) {
				double term = i + double(i) / j - j;
				sum += term * term; // додає квадрат виразу до суми
			}

			y *= sum; // множить y на отриману суму
		}
	}

	return y; // повертає результат
}

int main() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // налаштовує виведення українських літер
#endif

	showTitle("ВІТАЄМО! / WELCOME!", "ВІТАЄМО! / WELCOME!");

	cout << "  1 - Українська\n";
	cout << "  2 - English\n";
	cout << "------------------------------------------------------------\n";

	double choice; // зберігає вибір користувача

	// повторює вибір мови до правильного введення
	do {
		choice = readNumber("Мова / Language [1-2]: ");

		if (choice != 1 && choice != 2)
			cout << "Оберіть 1 або 2 / Choose 1 or 2\n";

	} while (choice != 1 && choice != 2);

	language = int(choice); // зберігає номер вибраної мови

	// повторює роботу головного меню
	while (true) {
		showTitle("КАЛЬКУЛЯТОР ФУНКЦІЇ", "FUNCTION CALCULATOR");

		cout << message(
			"  Вітаємо! Програма допоможе обчислити y для значень x\n"
			"  у вибраному діапазоні та покаже результати в таблиці\n"
			"  Задайте початкове x, кінцеве x, крок і n\n\n",
			"  Welcome! This program calculates y for values of x\n"
			"  in your chosen range and displays a results table\n"
			"  Enter the starting x, ending x, step and n\n\n");

		showFormula();

		cout << "\n------------------------------------------------------------\n";

		// показує пункти меню
		cout << message(
			"  ГОЛОВНЕ МЕНЮ\n\n"
			"  1 - Обчислити функцію\n"
			"  2 - Довідка та обмеження\n"
			"  0 - Вийти з програми\n",
			"  MAIN MENU\n\n"
			"  1 - Calculate function\n"
			"  2 - Help and constraints\n"
			"  0 - Exit the program\n");

		cout << "------------------------------------------------------------\n";

		// повторює лише запит вибору, якщо введено неправильний пункт
		do {
			choice = readNumber(message(
				"Ваш вибір [0-2]: ",
				"Your choice [0-2]: "));

			if (choice != 0 && choice != 1 && choice != 2)
				cout << message(
					"[!] Оберіть 0, 1 або 2\n",
					"[!] Choose 0, 1 or 2\n");

		} while (choice != 0 && choice != 1 && choice != 2);

		if (choice == 0) break; // виходить із циклу меню

		if (choice == 2) {
			showTitle("ДОВІДКА ТА ОБМЕЖЕННЯ", "HELP AND CONSTRAINTS");

			cout << message(
				"  Початкове x - початок діапазону\n"
				"  Кінцеве x - кінець діапазону\n"
				"  Крок - на скільки збільшується x\n"
				"  n - визначає межі сум і добутку у формулі\n\n"
				"  Правила введення:\n"
				"  - початкове x <= кінцевого x\n"
				"  - крок > 0\n"
				"  - n - ціле число від 2 до 100\n"
				"  - дробові числа вводяться через крапку\n"
				"  - максимум 1000 рядків результатів\n\n"
				"  Якщо помилитеся, програма попросить виправити\n"
				"  значення, кількість спроб не обмежена\n\n"
				"  Приклад: початкове x = -4, кінцеве x = -2\n"
				"  Крок = 1, n = 2\n"
				"  Для x = -4, -3, -2 отримаємо y = 5.5, 34, 34\n\n"
				"  При x >= -3 результат залежить лише від n\n"
				"  Надто великий результат позначається як переповнення\n",
				"  Starting x - the beginning of the range\n"
				"  Ending x - the end of the range\n"
				"  Step - how much x increases each time\n"
				"  n - sets the sum and product limits in the formula\n\n"
				"  Input rules:\n"
				"  - starting x <= ending x\n"
				"  - step > 0\n"
				"  - n must be an integer from 2 to 100\n"
				"  - use a decimal point for fractional numbers\n"
				"  - maximum 1000 result rows\n\n"
				"  If you make a mistake, you can correct the value\n"
				"  There is no limit on the number of attempts\n\n"
				"  Example: starting x = -4, ending x = -2\n"
				"  Step = 1, n = 2\n"
				"  For x = -4, -3, -2 we get y = 5.5, 34, 34\n\n"
				"  For x >= -3, the result depends only on n\n"
				"  A result that is too large is marked as overflow\n");

			waitForEnter();
			continue; // повертається до головного меню після довідки
		}

		showTitle("ВВЕДЕННЯ ДАНИХ", "INPUT PARAMETERS");

		cout << message(
			"  Початкове x <= кінцевого x, крок > 0\n"
			"  n - ціле число від 2 до 100\n"
			"  Використовуйте крапку для дробових чисел\n\n",
			"  Starting x <= ending x, step > 0\n"
			"  n must be an integer from 2 to 100\n"
			"  Use a decimal point for fractional numbers\n\n");

		// вводить початок діапазону
		double startX = readNumber(message(
			"Початкове x: ", "Starting x: "));

		double endX;

		// повторює введення кінцевого x до правильного значення
		while (true) {
			endX = readNumber(message("Кінцеве x: ", "Ending x: "));

			if (endX < startX) {
				cout << message(
					"[!] Кінцеве x має бути >= початкового x\n",
					"[!] Ending x must be >= starting x\n");
				continue;
			}

			// перевіряє чи різниця меж не спричиняє переповнення
			if (!isfinite(endX - startX)) {
				cout << message(
					"[!] Діапазон надто великий, введіть ближче кінцеве x\n",
					"[!] The range is too large, enter a closer ending x\n");
				continue;
			}

			break; // кінцеве x правильне
		}

		double step;
		double intervals;

		// повторює введення кроку до правильного значення
		while (true) {
			step = readNumber(message("Крок: ", "Step: "));

			if (step <= 0) {
				cout << message(
					"[!] Крок має бути більшим за нуль\n",
					"[!] The step must be greater than zero\n");
				continue;
			}

			// перевіряє чи крок достатній для зміни x
			if (startX < endX && startX + step == startX) {
				cout << message(
					"[!] Крок надто малий, введіть більший\n",
					"[!] The step is too small, enter a larger value\n");
				continue;
			}

			intervals = (endX - startX) / step;

			// обмежує таблицю до 1000 рядків
			if (!isfinite(intervals) || intervals + 1e-9 >= 1000) {
				cout << message(
					"[!] Забагато рядків, збільште крок\n"
					"    Дозволено максимум 1000 рядків\n",
					"[!] Too many rows, increase the step\n"
					"    A maximum of 1000 rows is allowed\n");
				continue;
			}

			break; // крок правильний
		}

		double enteredN;

		// повторює введення n до правильного значення
		while (true) {
			enteredN = readNumber(message(
				"Ціле n (2..100): ",
				"Integer n (2..100): "));

			// floor округлює вниз, тому порівняння виявляє дробове n
			if (enteredN < 2 || enteredN > 100 ||
				enteredN != floor(enteredN)) {

				cout << message(
					"[!] Введіть ціле n від 2 до 100\n",
					"[!] Enter an integer n from 2 to 100\n");
				continue;
			}

			break; // n правильне
		}

		int n = int(enteredN); // перетворює перевірене n на ціле число

		// знаходить кількість кроків із допуском на похибку
		int steps = int(floor(intervals + 1e-9));

		showTitle("РЕЗУЛЬТАТИ ОБЧИСЛЕННЯ", "CALCULATION RESULTS");

		cout << setprecision(10); // виводить до 10 значущих цифр

		cout << "  n = " << n
			<< message("  |  крок = ", "  |  step = ")
			<< step << "\n\n";

		// виводить заголовки та задає ширину стовпців
		cout << "  " << setw(18) << "x"
			<< "  |" << setw(22) << "y" << '\n';

		cout << "  --------------------+----------------------\n";

		// перебирає значення x від початкового
		for (int k = 0; k <= steps; k++) {
			double x = startX + k * step; // обчислює поточне x

			if (x > endX) x = endX; // виправляє вихід за межу через похибку

			double y = calculate(x, n); // обчислює y за формулою

			cout << "  " << setw(18) << x << "  |";

			if (isfinite(y))
				cout << setw(22) << y; // виводить скінченний результат
			else
				cout << message("  Переповнення", "  Overflow");

			cout << '\n';
		}

		cout << "  --------------------+----------------------\n";

		cout << message(
			"\n[OK] Обчислення завершено!\n",
			"\n[OK] Calculation complete!\n");

		waitForEnter(); // повернення до меню після натискання enter
	}

	showTitle("ДО ПОБАЧЕННЯ!", "GOODBYE!");

	cout << message(
		"  Дякуємо за користування програмою!\n\n",
		"  Thank you for using the program!\n\n");

	return 0; // завершує програму
}
