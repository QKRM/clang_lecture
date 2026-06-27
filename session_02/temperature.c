#include <stdio.h>

int main(void)
{
	double celsius;
	double fahrenheit;

	printf("=== 온도 변환기 ===\n\n");
	printf("[ 섭씨 → 화씨 ]  공식: F = C * 9.0 / 5.0 + 32\n");
	celsius = 0.0;
	fahrenheit = celsius * 9.0 / 5.0 + 32;
	printf("섭씨 %6.2f°C = 화씨 %6.2f°F\n", celsius, fahrenheit);
	celsius = 100.0;
	fahrenheit = celsius * 9.0 / 5.0 + 32;
	printf("섭씨 %6.2f°C = 화씨 %6.2f°F\n", celsius, fahrenheit);
	celsius = 37.0;
	fahrenheit = celsius * 9.0 / 5.0 + 32;
	printf("섭씨 %6.2f°C = 화씨 %6.2f°F  (체온)\n", celsius, fahrenheit);
	printf("\n[ 화씨 → 섭씨 ]  공식: C = (F - 32) * 5.0 / 9.0\n");
	fahrenheit = 32.0;
	celsius = (fahrenheit - 32) * 5.0 / 9.0;
	printf("화씨 %6.2f°F = 섭씨 %6.2f°C\n", fahrenheit, celsius);
	fahrenheit = 212.0;
	celsius = (fahrenheit - 32) * 5.0 / 9.0;
	printf("화씨 %6.2f°F = 섭씨 %6.2f°C\n", fahrenheit, celsius);
	fahrenheit = 98.6;
	celsius = (fahrenheit - 32) * 5.0 / 9.0;
	printf("화씨 %6.2f°F = 섭씨 %6.2f°C  (체온)\n", fahrenheit, celsius);
	return (0);
}
