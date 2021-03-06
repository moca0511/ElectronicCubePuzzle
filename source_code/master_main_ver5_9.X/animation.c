#include "animation.h"

char last_command_3 = 0;
char last_command_count_3 = 0;
char past_command_4 = 0;
char past_command_count_4[4] = {0, 0, 0, 0};
const char list_4[3][4] =
	{{'F', 'S', 'B', 'Z'},
	 {'U', 'E', 'D', 'Y'},
	 {'R', 'M', 'L', 'X'}};

// void set_all_LED_ARRAY(char color) {
//     for (unsigned int i = 0; i < LED_ARRAY_X; i++) {
//         for (unsigned int j = 0; j < LED_ARRAY_Y; j++) {
//             LED_ARRAY[i][j] = color;
//         }
//     }
// }

// void shuffle_state_CE(const unsigned int seed_number) {
//     char rand_CE[SHUFFLE_MAX];
//     char i;
//     srand(seed_number);

//     for (i = 0; i < SHUFFLE_MAX; i++) {
//         rand_CE[i] = 1 + rand() % (18 + 3 * 3);
//     }
//     for (i = 0; i < SHUFFLE_MAX; i++) {
//         command_turn_CE(CE_LIST[rand_CE[i]].name);
//     }
// }

char mode_cube_end;

char get_axis(const char *s) {
    char axis;
    for (axis = 0; axis < 3; axis++) {
        for (char i = 0; i < 4; i++)
            if (list_4[axis][i] == *(s + 0))
                return axis;
    }
    return axis;
}

void command_turn_ARRAY_3_end(void) {
    char s2[3] = {'\0', '\0', '\0'};

    const char s2_2[3] = {'\0', '2', '\''};
    if (last_command_3 == 0) {
        last_command_3 = 0;
        last_command_count_3 = 0;
        set_CES();
        //convert_ROTtoLED();
        //OUT_LED_ARRAY(LED_ARRAY, POWER);

        return;
    }
    last_command_count_3 %= 4;
    if (last_command_count_3 == 0) {
        last_command_3 = 0;
        last_command_count_3 = 0;

        set_CES();
        //convert_ROTtoLED();
        //OUT_LED_ARRAY(LED_ARRAY, POWER);
        return;
    }
    s2[1] = s2_2[last_command_count_3 - 1];
    s2[0] = last_command_3;
    last_command_3 = 0;
    last_command_count_3 = 0;
    //printf("%s\n", s2);


    //    if (SPI_special(ARRAY_skip_CS) == 1)
    //  mode_cube_end = 0;

    switch (s2[0]) {
        case 'Z':
            if (str_cmp_const(s2, "Z") == 0) {
                command_turn_ARRAY_2_3("F", "S", "B'");
            } else if (str_cmp_const(s2, "Z'") == 0) {
                command_turn_ARRAY_2_3("F'", "S'", "B");
            } else {
                command_turn_ARRAY_2_3("F", "S", "B'");
                command_turn_ARRAY_2_3("F", "S", "B'");
            }
            set_CES();
            //convert_ROTtoLED();
            //OUT_LED_ARRAY(LED_ARRAY, POWER);
            return;
        case 'Y':
            if (str_cmp_const(s2, "Y") == 0) {
                command_turn_ARRAY_2_3("U", "E'", "D'");
            } else if (str_cmp_const(s2, "Y'") == 0) {
                command_turn_ARRAY_2_3("U'", "E", "D");
            } else {
                command_turn_ARRAY_2_3("U", "E'", "D'");
                command_turn_ARRAY_2_3("U", "E'", "D'");
            }
            set_CES();
            //convert_ROTtoLED();
            //OUT_LED_ARRAY(LED_ARRAY, POWER);
            return;
        case 'X':
            if (str_cmp_const(s2, "X") == 0) {
                command_turn_ARRAY_2_3("R", "M'", "L'");
            } else if (str_cmp_const(s2, "X'") == 0) {
                command_turn_ARRAY_2_3("R'", "M", "L");
            } else {
                command_turn_ARRAY_2_3("R", "M'", "L'");
                command_turn_ARRAY_2_3("R", "M'", "L'");
            }
            set_CES();
            //convert_ROTtoLED();
            //OUT_LED_ARRAY(LED_ARRAY, POWER);
            return;
        default:
            break;
    }
    command_turn_ARRAY_2_2(s2);
    set_CES();
    //convert_ROTtoLED();
    //OUT_LED_ARRAY(LED_ARRAY, POWER);

    return;
}

void command_turn_ARRAY_3(const char *s) {
    if (last_command_3 != *(s + 0)) {
        command_turn_ARRAY_3_end();
        last_command_3 = *(s + 0);
        last_command_count_3 = 0;
    }
    command_turn_CE(s);
    switch (*(s + 1)) {
        case '\'':
            last_command_count_3 += 3;
            break;
        case '2':
            last_command_count_3 += 2;
            break;
        case '\0':
            last_command_count_3 += 1;
            break;
    }
    return;
}

void command_turn_ARRAY_2(const char *s) {
    command_turn_CE(s);

    switch (*s) {
        case 'Z':
            if (str_cmp_const(s, "Z") == 0) {
                command_turn_ARRAY_2_3("F", "S", "B'");
            } else if (str_cmp_const(s, "Z'") == 0) {
                command_turn_ARRAY_2_3("F'", "S'", "B");
            } else {
                command_turn_ARRAY_2_3("F", "S", "B'");
                command_turn_ARRAY_2_3("F", "S", "B'");
            }
            return;
        case 'Y':
            if (str_cmp_const(s, "Y") == 0) {
                command_turn_ARRAY_2_3("U", "E'", "D'");
            } else if (str_cmp_const(s, "Y'") == 0) {
                command_turn_ARRAY_2_3("U'", "E", "D");
            } else {
                command_turn_ARRAY_2_3("U", "E'", "D'");
                command_turn_ARRAY_2_3("U", "E'", "D'");
            }
            return;
        case 'X':
            if (str_cmp_const(s, "X") == 0) {
                command_turn_ARRAY_2_3("R", "M'", "L'");
            }
            if (str_cmp_const(s, "X'") == 0) {
                command_turn_ARRAY_2_3("R'", "M", "L");
            } else {
                command_turn_ARRAY_2_3("R", "M'", "L'");
                command_turn_ARRAY_2_3("R", "M'", "L'");
            }
            return;
        default:
            break;
    }
    command_turn_ARRAY_2_2(s);
    return;
}

char ARRAY_skip_CS;

void command_turn_ARRAY_2_2(const char *s) {
    char s2[3];
    s2[0] = *s;
    s2[2] = '\0';

    // if (SPI_special(ARRAY_skip_CS) == 1)
    //     mode_cube_end = 0;

    if (*s == 0)return;

    char mouitido = 1;
    if (*(s + 1) == '2') {
        s2[1] = '\0';
        mouitido = 2;
    } else {
        s2[1] = *(s + 1);
    }
    for (int j = 0; j < mouitido; j++) {
        for (int i = 0; i < 3; i++) {
            if (mode_cube_end == 0)
                break;
            TURN_COUNT %= 12;
            command_turn_ARRAY(s2);
            //axis_adjust_ARRAY();
            //convert_ROTtoLED();
            //OUT_LED_ARRAY(LED_ARRAY, POWER);
            //__delay_ms(100); //100
        }
        if (mode_cube_end == 0)
            continue;
        //convert_ROTtoLED();
        //OUT_LED_ARRAY(LED_ARRAY, POWER);

        //do1();
        //__delay_ms(95);
        TURN_COUNT = 0;
    }
    return;
}

void command_turn_ARRAY_2_3(const char *s1, const char *s2, const char *s3) {

    // if (SPI_special(ARRAY_skip_CS) == 1)
    //     mode_cube_end = 0;


    for (int i = 0; i < 3; i++) {
        if (mode_cube_end == 0)
            break;
        TURN_COUNT %= 12;
        command_turn_ARRAY(s1);
        command_turn_ARRAY(s2);
        command_turn_ARRAY(s3);
        //axis_adjust_ARRAY();
        //convert_ROTtoLED();
        //OUT_LED_ARRAY(LED_ARRAY, POWER);
        //__delay_ms(120); //80

        //preint_SET_LED_2();
        //set_CES();
    }
    if (mode_cube_end == 0)
        return;
    //set_CES();
    //convert_ROTtoLED();
    //OUT_LED_ARRAY(LED_ARRAY, POWER);

    //do1();
    //__delay_ms(100);
    TURN_COUNT = 0;
    return;
}
