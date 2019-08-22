// 17114024 Deepansh Nagaria
// C program to print class, networkID and hostID

#include<stdio.h> 
#include<string.h> 


char findClass(char str[]) 
{ 
	// storing first octet in arr[] variable 
	char arr[4]; 
	int index = 0; 
	while (str[index] != '.') 
	{ 
		arr[index] = str[index]; 
		index++; 
	} 
	index--; 

	int ip = 0, j = 1; 
	while (index >= 0) 
	{ 
		ip = ip + (str[index] - '0') * j; 
		j = j * 10; 
		index--; 
	} 

	if (ip >=1 && ip <= 126) 
		return 'A'; 

	else if (ip >= 128 && ip <= 191) 
		return 'B'; 

	else if (ip >= 192 && ip <= 223) 
		return 'C'; 

	else if (ip >= 224 && ip <= 239) 
		return 'D'; 
 
	else
		return 'E'; 
} 

// Function to util_separate Network ID as well as 
// Host ID and print them 
void util_separate(char str[], char ipClass) 
{ 
	// Initializing ntwork and host array to NULL 
	char ntwork[12], host[12]; 
	for (int k = 0; k < 12; k++) 
		ntwork[k] = host[k] = '\0'; 

	// for class A, only first octet is Network ID 
	// and rest are Host ID 
	if (ipClass == 'A') 
	{ 
		int index = 0, j = 0; 
		while (str[j] != '.') 
			ntwork[index++] = str[j++]; 
		index = 0; 
		j++; 
		while (str[j] != '\0') 
			host[index++] = str[j++]; 
		printf("Network ID is %s\n", ntwork); 
		printf("Host ID is %s\n", host); 
	} 

	// for class B, first two octet are Network ID 
	// and rest are Host ID 
	else if (ipClass == 'B') 
	{ 
		int index = 0, j = 0, dotCount = 0; 

		// storing in ntwork[] up to 2nd dot 
		// dotCount keeps track of number of 
		// dots or octets passed 
		while (dotCount < 2) 
		{ 
			ntwork[index++] = str[j++]; 
			if (str[j] == '.') 
				dotCount++; 
		} 
		index = 0; 
		j++; 

		while (str[j] != '\0') 
			host[index++] = str[j++]; 

		printf("Network ID is %s\n", ntwork); 
		printf("Host ID is %s\n", host); 
	} 

	// for class C, first three octet are Network ID 
	// and rest are Host ID 
	else if (ipClass == 'C') 
	{ 
		int index = 0, j = 0, dotCount = 0; 

		// storing in ntwork[] up to 3rd dot 
		// dotCount keeps track of number of 
		// dots or octets passed 
		while (dotCount < 3) 
		{ 
			ntwork[index++] = str[j++]; 
			if (str[j] == '.') 
				dotCount++; 
		} 

		index = 0; 
		j++; 

		while (str[j] != '\0') 
			host[index++] = str[j++]; 

		printf("Network ID is %s\n", ntwork); 
		printf("Host ID is %s\n", host); 
	} 

	// Class D and E are not divided in Network 
	// and Host ID 
	else
		printf("for this particular class "
		" divided into Network and Host ID are not defined \n"); 
} 


int main() 
{ 
	char str[] = "192.226.12.11"; 
	char ipClass = findClass(str); 
	printf("This address has the Class %c\n", 
										ipClass); 
	util_separate(str, ipClass); 
	return 0; 
} 
