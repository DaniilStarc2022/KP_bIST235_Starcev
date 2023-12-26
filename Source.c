#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#define MAX_MATERIAL_COUNT 100 // Максимальное количество строк в файле каталога
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct {
    double length;
    double width;
    double doorLength;
    double doorWidth;
} Room;

typedef struct {
    double length;
    double width;
    double costPerRoll;
    char name[20];
} Material;

Material linoleum = { 0, 0, 0, "линолеум" };
Material carpet = { 0, 0, 0, "ковролин" };
int calculationDone = 0, writeDataDone = 0, catalogUsing = 0;
double totalArea = 0.0;
int roomCount = 0;

Room inputRoomData(int roomNumber, int randomChoice);
void outputRoomData(Room* rooms, int roomCount);
int countRolls(double totalArea, Material material);
double calculateRoomArea(Room room);
double calculateTotalArea(Room* rooms, int roomCount);
int chooseMaterialType();
Material* inputMaterial(const char* name);

void writeDataToFile(Room* rooms, int roomCount, Material* selectedMaterial, double totalArea);
void readDataFromFile(const char fileName[]);

Material* readMaterialFromFile(const char* fileName, int* materialCount);
void printMaterialCatalog(Material* materials, int materialCount);
void calculateAndOutputMaterialUsage(Room* rooms, int roomCount, Material** selectedMaterial, double* totalArea, int inputMethod);


int main() {
    setlocale(LC_ALL, "RUS");
    int roomCount = 0;
    Room* rooms = NULL;

    int choice = 0;
    Material* selectedMaterial = NULL;

    while (choice != 7) {
        system("cls");
        printf("+***************************************************************************+\n");
        printf("*   Эта программа предназначена для расчета количества напольного покрытия  *\n");
        printf("*                                                                           *\n");
        printf("*          Выполнена студентом группы ИСТ-235 Старцевым Даниилом            *\n");
        printf("*                                                                           *\n");
        printf("+***************************************************************************+\n\n");
        printf("+***************************************************************************+\n");
        printf("*              Меню                                                         *\n");
        printf("* 1. Ввести количество комнат                                               *\n");
        printf("* 2. Ввести данные о комнатах                                               *\n");
        printf("* 3. Вывести данные о комнатах                                              *\n");
        printf("* 4. Рассчитать количество напольного покрытия                              *\n");
        printf("* 5. Записать информацию о  комнатах и напольном покрытие в файл            *\n");
        printf("* 6. Считать данные из файла                                                *\n");
        printf("*                                                                           *\n");
        printf("* 7. Завершение работы программы                                            *\n");
        printf("+***************************************************************************+\n");

        printf("\n Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
        {
            printf("Введите количество комнат: ");
            scanf("%d", &roomCount);
            if (roomCount <= 0) {
                printf("Некорректное количество комнат.\n");
            }
            else {
                if (rooms != NULL) {
                    free(rooms);
                }
                rooms = (Room*)malloc(roomCount * sizeof(Room));
                if (rooms == NULL) {
                    printf("Ошибка выделения памяти.\n");
                }
                else {
                    printf("Количество комнат успешно установлено.\n");
                }
            }
            system("\npause");
            break;
        }
        case 2:
        {
            if (!roomCount) {
                printf("Запишите сначала сведения о количестве комнат.\n");
                system("pause");
                break;
            }
            int randomChoice = 0;
            srand(time(NULL));
            printf("Выберите способ заполнения данных для комнаты (1 - случайные данные, 2 - ввод вручную): ");
            scanf("%d", &randomChoice);
            if(randomChoice != 1 && randomChoice !=2) {
                printf("Вы выбрали неверный пункт. Попробуйте еще раз!\n");
                system("\npause");
                break;
            }
            for (int i = 0; i < roomCount; i++) 
            {
                rooms[i] = inputRoomData(i + 1, randomChoice);
            }
            printf("Данные успешно записаны!\n");
            system("\npause");
            break;
        }
        case 3:
        {
            if (!writeDataDone) {
                printf("Запишите сначала сведения о размерах комнат.\n");
                system("pause");
                break;
            }
            outputRoomData(rooms, roomCount);
            system("\npause");
            break;
        }
        case 4:
        {
            if (!roomCount) {
                printf("Запишите сначала сведения о количестве комнат.\n");
                system("pause");
                break;
            }
            if (!writeDataDone) {
                printf("Запишите сначала сведения о размерах комнат.\n");
                system("pause");
                break;
            }
            printf("Выберите способ заполнения данных для комнаты (1 - ввод вручную, 2 - выбрать из каталога): ");
            int selection;
            scanf("%d", &selection);
            if (selection == 2) {
                int materialCount = 0;
                Material* materials = readMaterialFromFile("C:\\Users\\USER\\Desktop\\Visual Studio\\В28_Старцев_КП\\catalog.txt", &materialCount);
                printMaterialCatalog(materials, materialCount);
                int chosenMaterialIndex;
                printf("Выберите номер материала из каталога: ");
                scanf("%d", &chosenMaterialIndex);
                selectedMaterial = &materials[chosenMaterialIndex - 1];
                
            }
            calculateAndOutputMaterialUsage(rooms, roomCount, &selectedMaterial, &totalArea, selection);
            system("\npause");
            break;
        }
        case 5:
        {
            if (!calculationDone) {
                printf("Выполните сначала расчет количества напольного покрытия.\n");
                system("\npause");
                break;
            }
            writeDataToFile(rooms, roomCount, selectedMaterial, totalArea);
            system("\npause");
            break;

        }
        case 6:
        {
            printf("Введите название файла для чтения данных: ");
            char fileName[50];
            scanf("%s", fileName);
            char fullFileName[100] = "C:\\Users\\USER\\Desktop\\Visual Studio\\В28_Старцев_КП\\";
            strcat(fullFileName, fileName);

            readDataFromFile(fullFileName);
            system("pause");
            break;
        }
        case 7:
        {
            printf("Завершение работы программы, До свидания!\n");
            system("\npause");
            break;
        }
        default:
            printf("Некорректный выбор. Попробуйте снова.\n");
            system("\npause");
            break;
        }
    }

    if (rooms != NULL) {
        free(rooms);
        rooms = NULL; // Указатель присваивается NULL после освобождения памяти
    }

    return 0;
}



Room inputRoomData(int roomNumber, int randomChoice) {
    Room room;
    if (randomChoice == 2) {
        printf("\nВведите данные для комнаты %d:\n", roomNumber);
        printf("Длина комнаты (в метрах): ");
        scanf("%lf", &room.length);
        printf("Ширина комнаты (в метрах): ");
        scanf("%lf", &room.width);
        printf("Длина дверного проема (в метрах): ");
        scanf("%lf", &room.doorLength);
        printf("Ширина дверного проема (в метрах): ");
        scanf("%lf", &room.doorWidth);
    }
    else if(randomChoice == 1){
        room.length = ((double)rand() / RAND_MAX) * (10.7 - 1.5) + 1.5;
        room.width = ((double)rand() / RAND_MAX) * (10.7 - 1.5) + 1.5;
        room.doorLength = ((double)rand() / RAND_MAX) * (1.0 - 0.7) + 0.7;
        room.doorWidth = ((double)rand() / RAND_MAX) * (0.4 - 0.1) + 0.1;
    }
    writeDataDone = 1;
    return room;
}
void outputRoomData(Room* rooms, int roomCount) {
    for (int i = 0; i < roomCount; i++) {
        printf("\nДанные для комнаты %d:\n", i + 1);
        printf("Длина комнаты (в метрах): %.2lf м\n", rooms[i].length);
        printf("Ширина комнаты (в метрах): %.2lf м\n", rooms[i].width);
        printf("Длина дверного проема (в метрах): %.2lf м\n", rooms[i].doorLength);
        printf("Ширина дверного проема (в метрах): %.2lf м\n", rooms[i].doorWidth);
        printf("\n");
    }
}


double calculateRoomArea(Room room) {
    return (room.length * room.width) + (room.doorLength * room.doorWidth);
}
double calculateTotalArea(Room* rooms, int roomCount) {
    double totalArea = 0.0;
    for (int i = 0; i < roomCount; i++) {
        totalArea += calculateRoomArea(rooms[i]);
    }
    return totalArea;
}


int chooseMaterialType() {
    int choice;
    printf("\nВыберите тип напольного покрытия:\n");
    printf("1. Линолеум\n");
    printf("2. Ковролин\n");
    printf("Выберите: ");
    scanf("%d", &choice);
    return choice;
}
Material* inputMaterial(const char* name) {
    Material* newMaterial = (Material*)malloc(sizeof(Material));
    printf("Введите размеры рулона напольного покрытия (в метрах):\n");
    printf("Длина: ");
    scanf("%lf", &newMaterial->length);
    printf("Ширина: ");
    scanf("%lf", &newMaterial->width);
    printf("Стоимость за рулон: ");
    scanf("%lf", &newMaterial->costPerRoll);
    strncpy(newMaterial->name, name, sizeof(newMaterial->name));

    calculationDone = 1;

    return newMaterial;
}
int countRolls(double totalArea, Material material) {
    double areaPerRoll = material.length * material.width;
    int rolls = totalArea / areaPerRoll;
    if (totalArea > rolls * areaPerRoll) {
        rolls++;
    }
    return rolls;
}
void calculateAndOutputMaterialUsage(Room* rooms, int roomCount, Material** selectedMaterial, double* totalArea, int inputMethod) {
    if (inputMethod == 1) {
        int materialType = chooseMaterialType();
        switch (materialType) {
        case 1:
            *selectedMaterial = inputMaterial("линолеум");
            break;
        case 2:
            *selectedMaterial = inputMaterial("ковролин");
            break;
        default:
            printf("Некорректный выбор типа напольного покрытия.\n");
            return;
        }
    }
    else if (inputMethod == 2) {
        if (*selectedMaterial == NULL) {
            printf("Выберите материал из каталога перед расчётом.\n");
            return;
        }
    }

    *totalArea = calculateTotalArea(rooms, roomCount);
    int rolls = countRolls(*totalArea, **selectedMaterial);
    printf("\nОбщая площадь для покрытия: %.2lf м^2\n", *totalArea);
    printf("Для выбранного напольного покрытия (%s) потребуется:\n", (*selectedMaterial)->name);
    printf("Количество рулонов: %d\n", rolls);
    printf("Общая стоимость: %.2lf\n", rolls * (*selectedMaterial)->costPerRoll);
    calculationDone = 1;
}

void writeDataToFile(Room* rooms, int roomCount, Material* selectedMaterial, double totalArea) {
    if (!calculationDone) {
        printf("Выполните сначала расчет количества напольного покрытия.\n");
        return;
    }

    char fileName[50];
    printf("Введите имя файла для записи данных: ");
    scanf("%s", fileName);

    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }
    fprintf(file, "Данные о комнатах:\n");
    for (int i = 0; i < roomCount; i++) {
        fprintf(file, "\nДанные для комнаты %d:\n", i + 1);
        fprintf(file, "Длина комнаты (в метрах): %.2lf м\n", rooms[i].length);
        fprintf(file, "Ширина  комнаты (в метрах): %.2lf м\n", rooms[i].width);
        fprintf(file, "Длина дверного проема (в метрах): %.2lf м\n", rooms[i].doorLength);
        fprintf(file, "Ширина дверного проема (в метрах): %.2lf м\n", rooms[i].doorWidth);
        fprintf(file, "\n");
    }

    if (selectedMaterial != NULL) {
        int rolls = countRolls(totalArea, *selectedMaterial);

        fprintf(file, "\nДанные о напольном покрытии:\n");
        fprintf(file, "Тип материала: %s\n", selectedMaterial->name);
        fprintf(file, "Длина рулона: %.2lf м\n", selectedMaterial->length);
        fprintf(file, "Ширина рулона: %.2lf м\n", selectedMaterial->width);
        fprintf(file, "Стоимость за рулон (руб.): %.2lf\n", selectedMaterial->costPerRoll);
        fprintf(file, "\nОбщая площадь для покрытия: %.2lf  м^2\n", totalArea);
        fprintf(file, "\nДанные о расходах для покрытия комнат:\n");
        fprintf(file, "Количество рулонов: %d\n", rolls);
        fprintf(file, "Общая стоимость (руб.): %.2lf\n", rolls * selectedMaterial->costPerRoll);
    }

    fclose(file);
    printf("Данные успешно записаны в файл %s.\n", fileName);
}
void readDataFromFile(const char fileName[]) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла для чтения.\n");
        return;
    }

    Room rooms;
    Material material;
    char line[100];

    while (true) {
        int itemsRead = fscanf(file, "%*[^:]: %lf\n", &(rooms.length));
        if (itemsRead != 1) {
            break; // Прерываем цикл, если не удалось прочитать данные
        }

        fscanf(file, "%*[^:]: %lf\n", &(rooms.width));
        fscanf(file, "%*[^:]: %lf\n", &(rooms.doorLength));
        fscanf(file, "%*[^:]: %lf\n", &(rooms.doorWidth));
        fscanf(file, "%*[^:]: %s\n", material.name);
        fscanf(file, "%*[^:]: %lf\n", &(material.length));
        fscanf(file, "%*[^:]: %lf\n", &(material.width));
        fscanf(file, "%*[^:]: %lf\n", &(material.costPerRoll));

        double roomArea = (rooms.length * rooms.width) + (rooms.doorLength * rooms.doorWidth);
        double rollArea = material.length * material.width;
        int rollsNeeded = (int)(roomArea / rollArea);
        if (roomArea > rollsNeeded * rollArea) {
            rollsNeeded++;
        }
        double totalCost = rollsNeeded * material.costPerRoll;

        printf("Считанные данные из файла %s:\n\n", fileName);
        fseek(file, 0, SEEK_SET); // Переход к началу файла

        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }

        printf("\nРасчеты по данным из файла %s:\n\n", fileName);
        printf("Общая площадь для покрытия: %.2lf м^2\n", roomArea);
        printf("Для выбранного напольного покрытия потребуется:\n");
        printf("Количество рулонов: %d\n", rollsNeeded);
        printf("Общая стоимость: %.2lf руб.\n\n", totalCost);
    }

    fclose(file);
}
Material* readMaterialFromFile(const char* fileName, int* materialCount) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла для чтения.\n");
        return NULL;
    }

    Material* materials = (Material*)malloc(MAX_MATERIAL_COUNT * sizeof(Material));
    if (materials == NULL) {
        printf("Ошибка выделения памяти.\n");
        fclose(file);
        return NULL;
    }

    *materialCount = 0;
    char materialName[20];
    double materialLength, materialWidth, materialCost;

    while (*materialCount < MAX_MATERIAL_COUNT &&
        fscanf(file, "%s %lf %lf %lf\n", materialName, &materialLength, &materialWidth, &materialCost) == 4) {
        strcpy(materials[*materialCount].name, materialName);
        materials[*materialCount].length = materialLength;
        materials[*materialCount].width = materialWidth;
        materials[*materialCount].costPerRoll = materialCost;
        (*materialCount)++;
    }
    fclose(file);
    return materials;

}


void printMaterialCatalog(Material* materials, int materialCount) {
    printf("+------------------------------------------------------------------+\n");
    printf("| Номер | Материал  | Длина | Ширина | Стоимость за рулон (руб.)   |\n");
    printf("+------------------------------------------------------------------+\n");
    for (int i = 0; i < materialCount; i++) {
        printf("| %-6d| %-10s| %-6.2lf| %-7.2lf| %-25.2lf   |\n", i + 1, materials[i].name, materials[i].length, materials[i].width, materials[i].costPerRoll);
    }
    printf("+------------------------------------------------------------------+\n");
}

