package lab2;

public class ExtraSymbolsException extends RuntimeException {

    private final int pos;

    public ExtraSymbolsException(int pos) {
        super("Лишние символы на позиции " + pos);
        this.pos = pos;
    }
}
