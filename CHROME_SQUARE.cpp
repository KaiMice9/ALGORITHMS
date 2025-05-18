#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Проверяет, есть ли в профиле mask1 и mask2 хотя бы один монохромный квадрат 2x2
bool has_monochrome(int mask1, int mask2, int n) {
    for (int i = 0; i < n - 1; ++i) {
        // Проверяем квадрат из битов i и i+1 в mask1 и mask2
        bool top_left = (mask1 >> i) & 1;
        bool top_right = (mask1 >> (i + 1)) & 1;
        bool bottom_left = (mask2 >> i) & 1;
        bool bottom_right = (mask2 >> (i + 1)) & 1;
        
        // Если все 4 клетки одинаковые -> монохромный квадрат
        if (top_left == top_right && top_right == bottom_left && bottom_left == bottom_right) {
            return true;
        }
    }
    return false;
}

// Основная функция для подсчёта симпатичных узоров
int count_patterns(int n, int m) {
    if (n == 0 || m == 0) return 0;
    
    // Всего возможных масок для строки: 2^n
    int total_masks = 1 << n;
    
    // dp[i][mask] = количество способов для первых i столбцов с последней маской mask
    vector<vector<int>> dp(m + 1, vector<int>(total_masks, 0));
    
    // Базовый случай: первый столбец может быть любой маской
    for (int mask = 0; mask < total_masks; ++mask) {
        dp[1][mask] = 1;
    }
    
    // Переходы между столбцами
    for (int col = 2; col <= m; ++col) {
        for (int prev_mask = 0; prev_mask < total_masks; ++prev_mask) {
            for (int curr_mask = 0; curr_mask < total_masks; ++curr_mask) {
                // Проверяем, что нет монохромных квадратов между prev_mask и curr_mask
                if (!has_monochrome(prev_mask, curr_mask, n)) {
                    dp[col][curr_mask] += dp[col - 1][prev_mask];
                }
            }
        }
    }
    
    // Суммируем все валидные раскраски для последнего столбца
    int result = 0;
    for (int mask = 0; mask < total_masks; ++mask) {
        result += dp[m][mask];
    }
    
    return result;
}

int main() {
    int n = 2;  // Количество строк
    int m = 3;  // Количество столбцов
    
    cout << "Количество симпатичных узоров для сетки " 
         << n << "x" << m << ": " << count_patterns(n, m) << endl;
    
    return 0;
}