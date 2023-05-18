#include <iostream>
using namespace std;

void plusMinus(float*& nums, char*& works, int& i)
{
	int j{};
	if (works[i] == '+')
		nums[i] = nums[i] + nums[i + 1];

	else if (works[i] == '-')
		nums[i] = nums[i] - nums[i + 1];

	if (nums[i + 1] != '\0')
		j = i + 1;
	else
		j = i;
	while (nums[j + 1] != '\0')
	{
		nums[j] = nums[j + 1];
		j++;
	}
	j = i;
	while (works[j] != '\0')
	{
		works[j] = works[j + 1];
		j++;
	}
	i--;
}

void multidivision(float*& nums, char*& works, int& i)
{
	int j{};
	if (works[i] == '*')
		nums[i] = nums[i] * nums[i + 1];
	else if (works[i] == '/')
		nums[i] = nums[i] / nums[i + 1];

	if (nums[i + 1] != '\0')
		j = i + 1;
	else
		j = i;
	while (nums[j + 1] != '\0')
	{
		nums[j] = nums[j + 1];
		j++;
	}
	j = i;
	while (works[j] != '\0')
	{
		works[j] = works[j + 1];
		j++;
	}
	i--;
}

char* examination(float*& nums, char*& works)
{
	bool close = true;
	char* arr = new char[401] {};
	char* works = new char[20] {};
	while (close)
	{
		nums = new float[200] {};
		works = new char[200] {};

		cout << "Enter example: "; cin.getline(arr, 100);

		for (size_t i{}; (int)arr[i] != (int)'\0'; i++)
		{
			if (((int)arr[i] < 48 || (int)arr[i] > 57) && arr[i] != ' ' && ((int)arr[i] < 40 || (int)arr[i] > 47))
				continue;
		}
		close = false;

		for (size_t a = 0, j{}, v{}, z{}; (int)arr[a] != (int)'\0'; a++)
		{
			if ((int)arr[a] > 47 && (int)arr[a] < 58)
			{
				nums[j] = (int)arr[a] - (int)'0';
				while ((int)arr[a + 1] > 47 && (int)arr[a + 1] < 58)
				{
					nums[j] *= 10;
					a++;
					nums[j] += (int)arr[a] - (int)'0';
				}
				j++;
			}
			else if ((int)arr[a] == '(' && (int)arr[a + 1] == '-')
			{
				a += 2;
				if ((int)arr[a] > 47 && (int)arr[a] < 58)
				{
					nums[j] = (int)arr[a] - (int)'0';
					while ((int)arr[a + 1] > 47 && (int)arr[a + 1] < 58)
					{
						nums[j] *= 10;
						a++;
						nums[j] += (int)arr[a] - (int)'0';
					}
					nums[j] *= -1;
					j++;
				}
				if (arr[a + 1] != ')')
				{
					close = true;
					continue;
				}
				else
					a++;
			}
			else if ((int)arr[a] > 39 && (int)arr[a] < 48)
			{
				if (arr[a] == '(' || arr[a] == ')')
				{
					works[z] = arr[a];
					z++;
				}
				else
				{
					works[v] = arr[a];
					v++;
					works[z] = arr[a];
					z++;
				}
			}
		}
		int l1{}, l2{};
		while (nums[l1] != '\0')
			l1++;
		while (works[l2] != '\0')
			l2++;

		if (l1 == l2 || l2 > l1)
		{
			close = true;
			continue;
		}
	}

	for (size_t i = 0; works[i] != '\0'; i++)
	{
		if (works[i] == ')')
		{
			for (size_t j = i - 1; works[j] != '('; j--)
			{
				if (works[j] == '*' || works[j] == '/')
				{
					int v = j - 1;
					multidivision(nums, works, v);
					int z = j;
					for (z; works[z] != '\0'; z++)
						works[z] = works[z + 1];
					works[z - 1] = '\0';
					j--;
				}
			}
			for (int j = i - 1; works[j] != '('; j--)
			{
				if (works[j] == '+' || works[j] == '-')
				{
					int v = j - 1;
					plusMinus(nums, works, v);
					int z = j;
					for (z; works[z] != '\0'; z++)
						works[z] = works[z + 1];
					works[z - 1] = '\0';
					j--;
				}
				int l = i;
				for (l; works[l] != '\0'; l++)
					works[l] = works[l + 1];
				works[l] == '\0';
				i--;
			}

		}
	}
	return arr;
}

int main()
{
	bool close = true;
	while (close)
	{
		char* arr{};
		float* nums{};
		char* works{};

		arr = examination(nums, works);

		for (int i = 0; works[i] != '\0'; i++)
		{
			if (works[i] == '*' || works[i] == '/')
				multidivision(nums, works, i);
		}

		for (int i = 0; works[i] != '\0'; i++)
		{
			if (works[i] == '+' || works[i] == '-')
				plusMinus(nums, works, i);
		}

		cout << "Result: " << nums[0] << endl;

		cout << "Enter 0 to close: "; cin >> close;
		cin.ignore();
	}
	return 0;
}