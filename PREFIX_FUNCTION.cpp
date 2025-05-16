#include <vector>
#include <string>
#include <iostream>

// Вычисление префикс-функции для строки
std::vector<int> compute_prefix_function(const std::string& s) {
    int n = s.length();
    std::vector<int> pi(n, 0);  // Инициализируем массив префикс-функции нулями

    for (int i = 1; i < n; ++i) {  // pi[0] всегда 0, начинаем с 1
        int j = pi[i - 1];  // Длина предыдущего совпадающего префикса

        // Пытаемся расширить предыдущий префикс
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];  // "Откатываем" j по уже вычисленным значениям
        }

        // Если символы совпали, увеличиваем длину префикса
        if (s[i] == s[j]) {
            ++j;
        }

        pi[i] = j;  // Записываем результат
    }

    return pi;
}

int main() {
    std::string text = "abacabadabacaba";
    std::vector<int> prefix = compute_prefix_function(text);

    std::cout << "Префикс-функция для строки \"" << text << "\":\n";
    for (int i = 0; i < prefix.size(); ++i) {
        std::cout << "pi[" << i << "] = " << prefix[i] << "\n";
    }

    return 0;
}