
char ITA2L(int combination_number)
{
    if (!(combination_number >= 1 && combination_number <= 32))
        return ' ';
    if (combination_number <= 26)
        return 'A' + combination_number - 1;
    switch (combination_number)
    {
    case 27:
        return '\r';
    case 28:
        return '\n';
    case 31:
        return ' ';
    default:
        return ' ';
    }
}

char ITA2F(int combination_number)
{
    if (!(combination_number >= 1 && combination_number <= 32))
        return ' ';
    switch (combination_number)
    {
    case 1:
        return '-';
    case 2:
        return '?';
    case 3:
        return ':';
    case 5:
        return '3';
    case 9:
        return '8';
    case 10:
        return '\007';
    case 11:
        return '(';
    case 12:
        return ')';
    case 13:
        return '.';
    case 14:
        return ',';
    case 15:
        return '9';
    case 16:
        return '0';
    case 17:
        return '1';
    case 18:
        return '4';
    case 20:
        return '5';
    case 21:
        return '7';
    case 22:
        return '=';
    case 23:
        return '2';
    case 24:
        return '/';
    case 25:
        return '6';
    case 26:
        return '+';
    default:
        return ' ';
    }
}

