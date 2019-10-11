#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
    printf("%s:\n",t.name);
    for(int i = 0; i<t.offices_count;i++){
        printf("\t%d:\n",i);
        struct post_office* post = &(t.offices[i]);
        for(int p = 0; p < post->packages_count ;p++){
            printf("\t\t%s\n",post->packages[p].id);
        }
    }
}

void print_all_packages_office(post_office post) {
    for(int p = 0; p < post.packages_count ;p++){
        printf("\t\t%s\n",post.packages[p].id);
    } 
}

void transfer_package(post_office* source, post_office* target, int source_index){
    // Make space at target
    //printf("Target Before:\n");
    //print_all_packages_office(*target);

    target->packages_count++;
    target->packages = (package*) realloc(target->packages,sizeof(package)*target->packages_count);

    // Copy package to target
    target->packages[target->packages_count-1] = source->packages[source_index];

    //printf("Target After:\n");
    //print_all_packages_office(*target);

    //printf("Source Before(%d):\n",source->packages_count);
    //print_all_packages_office(*source);
    // Remove package from source by shifting packages up the queue.
    for(int p = source_index; p < (source->packages_count-1); p++){
        //printf("packages[%d] was %s ", p, source->packages[p].id);
        source->packages[p] = source->packages[p+1];
        //printf("but is now %s\n", source->packages[p].id);
    }
    //printf("Source After Shifting(%d):\n",source->packages_count);
    //print_all_packages_office(*source);

    // Shorten space allocated to source office, cause it has 1 less package
    source->packages_count--;
    source->packages = (package*) realloc(source->packages, sizeof(package)*source->packages_count);
    
    //printf("Source After Realloc(%d):\n",source->packages_count);
    //print_all_packages_office(*source);
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
    // Assign pointers to post offices
    post_office* source_office = &(source->offices[source_office_index]);
    post_office* target_office = &(target->offices[target_office_index]);

    // Loop through packages at source office
    int min = target_office->min_weight;
    int max = target_office->max_weight;
    for(int p = 0; p<source_office->packages_count;p++){
        // Check size
        int weight = source_office->packages[p].weight;
        if(weight >= min && weight <= max){
            // Send package
            transfer_package(source_office, target_office, p);
            // Have to check the current index again since transfer shifts everything
            p--;
        }
    }
}

town town_with_most_packages(town* towns, int towns_count) {
    town* most = 0;
    int maxpackages = 0;
 
    for(int t = 0; t < towns_count; t++){
        int numpackages = 0;
        for(int o = 0; o<towns[t].offices_count;o++){
            numpackages += towns[t].offices[o].packages_count;
        }
        if(numpackages>maxpackages){
            maxpackages = numpackages;
            most = &towns[t];
        }
    }
    return *most;
}

town* find_town(town* towns, int towns_count, char* name) {
    town* target = 0;
    for(int t = 0; t<towns_count;t++){
        if(strcmp(towns[t].name,name)==0)
        {
            target = &towns[t];
            break;
        }
    }
    return target;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
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

