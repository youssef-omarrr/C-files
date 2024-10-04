#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
    char *id;
    int weight;
};

typedef struct package package;

struct post_office
{
    int min_weight;
    int max_weight;
    package *packages;
    int packages_count;
};

typedef struct post_office post_office;

struct town
{
    char *name;
    post_office *offices;
    int offices_count;
};

typedef struct town town;

void print_all_packages(town t)
{
    printf("%s:", t.name);
    for (int i = 0; i < t.offices_count; i++)
    {
        printf("\n\t%d:", i);
        for (int j=0; j< t.offices[i].packages_count; j++)
            printf("\n\t\t%s", t.offices[i].packages[j].id);
    }
    
    printf("\n");
}

void send_all_acceptable_packages(town *source, int source_office_index, town *target, int target_office_index)
{
    // Get the source and target post offices by their respective indices
    // make them as pointers to change the actuall office
    post_office *source_office = &source->offices[source_office_index];
    post_office *target_office = &target->offices[target_office_index];

    // Variable to keep track of the new total package count for the target office
    int new_target_count = target_office->packages_count;

    // Loop through all packages in the source office
    for (int i = 0; i < source_office->packages_count; i++)
    {
        // Access the current package from the source office
        package current_package = source_office->packages[i];

        // package wight within range
        if (current_package.weight <= target_office->max_weight 
        && current_package.weight >= target_office->min_weight)
        {
            new_target_count++;
            // Reallocate memory for the target office's package array to fit the new package
            target_office->packages = realloc(target_office->packages, sizeof(package) * new_target_count);

            // Add the current package to the end of the target office's package list
            target_office->packages[new_target_count - 1] = current_package;

            // Remove the transferred package from the source office by shifting the rest of the packages left
            // This overwrites the current package with the next one, moving all subsequent packages one position left
            for (int j = i; j < (source_office->packages_count) - 1; j++)
                source_office->packages[j] = source_office->packages[j + 1];
            

            // Decrease the package count in the source office as one package is transferred
            source_office->packages_count--;
            
            // Reallocate the source office's package array
            source_office->packages = realloc(source_office->packages, sizeof(package) * source_office->packages_count);


            // Decrement the loop index 'i' to account for the shifted packages
            // This ensures we don't skip the next package after shifting
            i--;
        }
    }

    // Update the target office's package count to reflect the newly added packages
    target_office->packages_count = new_target_count;
}


town town_with_most_packages(town *towns, int towns_count)
{
    // select first town
    town max_town = towns[0];
    int max_pack = 0;

    // Calculate total number of packages in the first town
    for (int i = 0; i < towns[0].offices_count; i++)
    {
        max_pack += towns[0].offices[i].packages_count;
    }

    // Compare with other towns
    for (int i = 1; i < towns_count; i++)
    {
        int current_pack = 0;

        // Calculate total number of packages in current town
        for (int j = 0; j < towns[i].offices_count; j++)
        {
            current_pack += towns[i].offices[j].packages_count;
        }

        if (current_pack > max_pack)
        {
            max_town = towns[i];
            max_pack = current_pack;
        }
    }
    return max_town;
}

town *find_town(town *towns, int towns_count, char *name)
{
    for (int i=0; i<towns_count; i++){
        if (!strcmp(towns[i].name, name))
            return &towns[i];
    }
    
    return NULL;
}

int main()
{
    int towns_count;
    scanf("%d", &towns_count);
    town *towns = malloc(sizeof(town) * towns_count);
    for (int i = 0; i < towns_count; i++)
    {
        towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(sizeof(post_office) * towns[i].offices_count);
        for (int j = 0; j < towns[i].offices_count; j++)
        {
            scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = malloc(sizeof(package) * towns[i].offices[j].packages_count);
            for (int k = 0; k < towns[i].offices[j].packages_count; k++)
            {
                towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }
    int queries;
    scanf("%d", &queries);
    char town_name[MAX_STRING_LENGTH];
    while (queries--)
    {
        int type;
        scanf("%d", &type);
        switch (type)
        {
        case 1:
            scanf("%s", town_name);
            town *t = find_town(towns, towns_count, town_name);
            print_all_packages(*t);
            break;
        case 2:
            scanf("%s", town_name);
            town *source = find_town(towns, towns_count, town_name);
            int source_index;
            scanf("%d", &source_index);
            scanf("%s", town_name);
            town *target = find_town(towns, towns_count, town_name);
            int target_index;
            scanf("%d", &target_index);
            send_all_acceptable_packages(source, source_index, target, target_index);
            break;
        case 3:
            printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
            break;
        }
    }
    return 0;
}
