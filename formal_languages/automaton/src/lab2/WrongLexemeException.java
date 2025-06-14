package lab2;

public class WrongLexemeException extends RuntimeException {

    private final int pos;
    private String lexemeAttribute;

    public WrongLexemeException(String lexemeAttribute, int pos) {
        super("Ожидается " + lexemeAttribute + " на позиции " + pos);
        this.lexemeAttribute = lexemeAttribute;
        this.pos = pos;
    }

    public WrongLexemeException(String lexemeAttribute1, String lexemeAttribute2, int pos) {
        super("Ожидается " + lexemeAttribute1 + " или " + lexemeAttribute2 + " на позиции " + pos);
        this.lexemeAttribute = lexemeAttribute1;
        this.pos = pos;
    }
}
