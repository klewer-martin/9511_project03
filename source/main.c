#include "../include/io.h"
#include "../include/cla.h"
#include "../include/user.h"
#include "../include/sort.h"
#include "../include/status.h"
#include "../include/vector.h"

#define BUFFER_INIT_SIZE	100
#define INPUT_FILE_DELIM	","
#define INPUT_FILE_FIELDS	6	

int main (int argc, char *argv[])
{
	status_t st;
	cla_t cla;
	ADT_Vector_t *v;
	ADT_user_t *user, *user_tmp;
	char *b, *endptr;
	char **data;
	size_t i, j;
	FILE *fi;
	long amount;

	user = NULL;

	/* Valida que los argumentos sean correctos */
	if((st = validate_arguments(argc, argv)) != OK) {
		show_status(st);
		return st;
	}

	/* Asigna memoria a cla */
	if((st = cla_create(&cla)) != OK) {
		show_status(st);
		return st;
	}

	/* Crea un vector */
	if((st = ADT_Vector_create(&v)) != OK) {
		show_status(st);
		cla_destroy(&cla);
		return st;
	}

	if((st = ADT_Vector_set_printer(v, user_printer)) != OK) {
		show_status(st);
		cla_destroy(&cla);
		ADT_Vector_destroy(&v);
		return st;
	}

	/* Asigna a la estructura 'cla' los argumentos ingresados */
	if((st = cla_setup(argc, argv, &cla)) != OK) {
		show_status(st);
		cla_destroy(&cla);
		ADT_Vector_destroy(&v);
		return st;
	}


	b = calloc(sizeof(char), BUFFER_INIT_SIZE);
	data = malloc(sizeof(char *) * INPUT_FILE_FIELDS);

	if(b == NULL || data == NULL) {
		free(b);
		show_status(ERROR_MEMORY);
		cla_destroy(&cla);
		ADT_Vector_destroy(&v);
		return ERROR_MEMORY;
	}

	/* Asigna memoria cada puntero dentro de data */
	for(i = 0; i < INPUT_FILE_FIELDS; i++) {
		if((data[i] = calloc(sizeof(char), BUFFER_INIT_SIZE)) == NULL) {
			show_status(ERROR_MEMORY);
			for(j = 0; j < i; j++)
				free(data[j]);

			free(b);
			cla_destroy(&cla);
			ADT_Vector_destroy(&v);
			return ERROR_MEMORY;
		}
	}
		
	/* Abre el archivo de entrada */
	if((fi = fopen(cla->fi, "rt")) == NULL) {
		show_status(ERROR_OPENING_FILE);
		for(j = 0; j < INPUT_FILE_FIELDS; j++)
			free(data[j]);

		free(b);
		cla_destroy(&cla);
		ADT_Vector_destroy(&v);
		return ERROR_OPENING_FILE;
	}

	ADT_Vector_set_comparator(v, user_id_equal);

	user_tmp = NULL;
	user_create(&user_tmp);

	while(fgets(b, BUFFER_INIT_SIZE, fi)) {
		string_split(b, data, INPUT_FILE_DELIM);
		user_set_data(user_tmp, data);

		amount = strtol(data[POS_AMOUNT], &endptr, 10);
		if(*endptr != '\0') return ERROR_CORRUPT_DATA;

		if((user = ADT_Vector_get_elem(v, user_tmp)) != NULL) {
			/* El usuario ya existe */
			user_add_amount(user, amount);
		}
		else { 
			/* El usuario no existe */
			user_create(&user);
			user_set_data(user, data);
			ADT_Vector_add(&v, user);
		}
	}

	ADT_Vector_sort(v, user_comparator_credits_maxmin);

	ADT_Vector_print(v, stdout);

	for(j = 0; j < INPUT_FILE_FIELDS; j++)
		free(data[j]);

	free(data);
	free(b);
	free(user_tmp);
	fclose(fi);
	cla_destroy(&cla);
	ADT_Vector_destroy(&v);
	return OK;
}






/*

// "ca" - creditos ascendentes | "cd" - creditos descendentes
// "da" - debitos ascendentes  | "dd" - debitos descendentes
#define SORTING_ORDER	"cd"
#define PRINT_EXIT_SUCCESS_MSG



#ifdef PRINT_EXIT_SUCCESS_MSG

	// Imprime un mensaje para darle a conocer al usuario
	// que todo se ejecuto correctamente
	printf("\n%s\n%s%ld\n%s%ld\n", EXIT_SUCCESS_MSG, USERS_REGISTERED_MSG,\
			size, PROCESED_LINES_MSG, cla->parsed_lines);

#endif
*/


	/* Carga en users los usuarios desde el archivo de entrada */
	/* if((st = process_file(cla, &users, &size)) != OK) { */
	/* 	show_status(st); */
	/* 	cla_destroy(&cla); */
	/* 	destroy_users(users, size); */
	/* 	return st; */
	/* } */

	/* Ordena los usuarios con orden SORTING_ORDER */
	/* if((st = sort_users(users, size, SORTING_ORDER)) != OK) { */
	/* 	show_status(st); */
	/* 	cla_destroy(&cla); */
	/* 	destroy_users(users, size); */
	/* 	return st; */
	/* } */

	/* Imprime los datos cargados en users a un archivo de salida */
	/* if((st = export_data(cla, users, size)) != OK) { */
	/* 	show_status(st); */
	/* 	cla_destroy(&cla); */
	/* 	destroy_users(users, size); */
	/* 	return st; */
	/* } */
