/*
 ============================================================================
 Name        : VehicleControlSystem.c
 Author      : Mazen Helmi
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1 //run the code lines that are related to the “Engine Temperature Controller" when 1 else doesn't run

struct state // structure to view the vehicle state
{
	char *EngineState;
	char *AC;
	int VehicleSpeed;
	int RoomTemp;
	char *EngineTempControllerState;
	int EngineTemp;
};

void VehicleControlSystem_Start();
void Main_Menu();
void EngineOn_Menu();
void EngineOnControl_Menu(char *ptr);
void PrintState(struct state *x);
void SetVehicleSpeed(char *ptr, struct state *x);
void SetRoomTemp(struct state *x);
void SetEngineTemp(struct state *x);

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	VehicleControlSystem_Start();

	return 0;
}

void VehicleControlSystem_Start() // function that Starts Program
{
	int run = 1; // condition to keep the program running
	char input; // variable for user input in Main Menu

	Main_Menu(); // printing Main Menu the first time only

	while(run == 1)
	{
		scanf(" %c", &input); //space before %c to prevent scanf function from take new line or enter from the above printf functions as input

		switch(input)
		{
		case 'a':
			printf("Turn on vehicle engine\n\n");
			EngineOnControl_Menu(&input);
			break;

		case 'b':
			printf("Turn off vehicle engine\n\n");
			Main_Menu();
			break;

		case 'c':
			printf("Quit the system");
			run = 0;
			break;

		default:
			printf("Invalid input. Try again\n\n");
			Main_Menu();
		}
	}
}

void Main_Menu(void) // function to print Main Menu
{
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
}

void EngineOn_Menu(void) // function to print Engine On Menu
{
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature\n\n");
#endif
}

void EngineOnControl_Menu(char *ptr)
{
	int run = 1; // condition to stay in Engine On Menu
	struct state current_state = {"ON", "OFF", 0, 35, "OFF", 90}; // Initialising the vehicle state

	EngineOn_Menu();

	while(run == 1)
	{
		scanf(" %c", ptr); //space before %c to prevent scanf function from take new line or enter from the above printf functions as input

		switch(*ptr)
		{

		case 'a':
			printf("Turn off vehicle engine\n\n");
			run = 0;
			Main_Menu();
			break;

		case 'b':
			SetVehicleSpeed(ptr, &current_state);
			PrintState(&current_state);
			EngineOn_Menu();
			break;

		case 'c':
			SetRoomTemp(&current_state);
			PrintState(&current_state);
			EngineOn_Menu();
			break;

		case 'd':
#if WITH_ENGINE_TEMP_CONTROLLER
			SetEngineTemp(&current_state);
#endif
			PrintState(&current_state);
			EngineOn_Menu();
			break;

		default:
			printf("Invalid input. Try again\n\n");
			EngineOn_Menu();
		}
	}
}

void PrintState(struct state *x) // function to print state structure... NOTE: this function can only be used inside the Engine Control Menu Function
{
	printf("\nEngine State: %s\n", x->EngineState);
	printf("AC: %s\n", x->AC);
	printf("Vehicle Speed = %d km/hr\n", x->VehicleSpeed);
	printf("Room Temperature = %d C\n", x->RoomTemp);
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("Engine Temperature Controller State: %s\n", x->EngineTempControllerState);
	printf("Engine Temperature = %d C`\n\n", x->EngineTemp);
#endif
}

void SetVehicleSpeed(char *ptr, struct state *x)
{
	printf("Sensor color input: ");
	scanf(" %c", ptr);

	if(*ptr == 'G' || *ptr == 'g')
		(*x).VehicleSpeed = 100;
	else if(*ptr == 'O' || *ptr == 'o')
		(*x).VehicleSpeed = 30;
	else if(*ptr == 'R' || *ptr == 'r')
		(*x).VehicleSpeed = 0;

	if((*x).VehicleSpeed == 30)
	{
		(*x).AC = "ON";
		(*x).RoomTemp = (*x).RoomTemp*(5/4)+1;
#if WITH_ENGINE_TEMP_CONTROLLER
		(*x).EngineTempControllerState = "ON";
		(*x).EngineTemp = (*x).EngineTemp*(5/4)+1;
#endif
	}
}

void SetRoomTemp(struct state *x)
{
	int input;

	printf("Temperature sensor reading: ");
	scanf("%d", &input);

	if(input < 10)
	{
		(*x).AC = "ON";
		(*x).RoomTemp = 20;
	}
	else if(input > 30)
	{
		(*x).AC = "ON";
		(*x).RoomTemp = 20;
	}
	else
	{
		(*x).AC = "OFF";
		(*x).RoomTemp = input;
	}
}

#if WITH_ENGINE_TEMP_CONTROLLER
void SetEngineTemp(struct state *x)
{
	int input;

	printf("Engine temperature sensor reading: ");
	scanf("%d", &input);

	if(input < 100)
	{
		(*x).EngineTempControllerState = "ON";
		(*x).EngineTemp = 125;
	}
	else if(input > 150)
	{
		(*x).EngineTempControllerState = "ON";
		(*x).EngineTemp = 125;
	}
	else
	{
		(*x).EngineTempControllerState = "OFF";
		(*x).EngineTemp = input;
	}
}
#endif
