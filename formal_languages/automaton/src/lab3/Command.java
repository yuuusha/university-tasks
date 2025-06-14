package lab3;

public enum Command {
    JMP, // безусловный переход
    JZ, // переход по лжи
    SET, // присваивание
    ADD, // сложение
    SUB, // вычитание
    CMPE, // ==
    CMPNE, // !=
    CMPL, // <
    CMPLE, // <=
    CMPG, // >
    CMPGE, // >=
    NOT; // !

    @Override
    public String toString() {
        return switch (this) {
            case JMP -> "JMP";
            case JZ -> "JZ";
            case SET -> "SET";
            case ADD -> "ADD";
            case SUB -> "SUB";
            case CMPE -> "CMPE";
            case CMPNE -> "CMPNE";
            case CMPL -> "CMPL";
            case CMPLE -> "CMPLE";
            case CMPG -> "CMPG";
            case CMPGE -> "CMPGE";
            case NOT -> "NOT";
            default -> super.toString();
        };
    }
}
