typedef string::const_iterator State;
Def expr(State &i);
Def term(State &i);
Def factor(State &i);
Def number(State &i);
void consume(State &i, char expected) {
    if (*i == expected)
        i++;
    else {
        exit(0);
    }
}
Def expr(State &i) {
    Def out = term(i);
    while (*i == '+' || *i == '-') {
        char op = *i;
        i++;
        Def out1 = term(i);
        if (op == '+')
            out += out1;
        else
            out -= out1;
    }
    return out;
}
Def term(State &i) {
    Def out = factor(i);
    while (*i == '*' || *i == '/') {
        char op = *i;
        i++;
        Def out1 = factor(i);
        if (op == '*')
            out *= out1;
        else
            out /= out1;
    }
    return out;
}
Def factor(State &i) {
    if (isdigit(*i))
        return number(i);
    //'('
    i++;
    Def out = expr(i);
    i++;
    return out;
}
Def number(State &i) {
    Def out = 0;
    while (isdigit(*i))
        out = out * 10 + *(i++) - '0';
    return out;
}
int main() {
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        State begin = s.begin();
        cout << expr(begin) << endl;
    }
}
