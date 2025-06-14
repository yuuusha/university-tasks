package lab1;

import java.util.List;

public class Lexeme {
    private final LexemeType lexemeType;
    private final LexemeCategory lexemeCategory;
    private final String value;
    private final int pos;

    public Lexeme(LexemeType lexemeType, LexemeCategory lexemeCategory, String value, int pos) {
        this.lexemeType = lexemeType;
        this.lexemeCategory = lexemeCategory;
        this.value = value;
        this.pos = pos;
    }

    public LexemeType getLexemeType() {
        return lexemeType;
    }

    public LexemeCategory getLexemeCategory() {
        return lexemeCategory;
    }

    public String getValue() {
        return value;
    }

    public int getPos() {
        return pos;
    }

    @Override
    public String toString() {
        return "Lexeme{" +
                "lexemeType=" + lexemeType +
                ", lexemeCategory=" + lexemeCategory +
                ", value='" + value + '\'' +
                ", pos='" + pos + '\'' +
                '}';
    }

    public static void printLexemeTable(List<Lexeme> lexemes) {
        int lexemeTypeWidth = lexemes.stream().mapToInt(l -> l.getLexemeType().toString().length()).max().orElse(10);
        int lexemeCategoryWidth = Math.max(lexemes.stream().mapToInt(l -> l.getLexemeCategory().toString().length()).max().orElse(17), 17);
        int valueWidth = lexemes.stream().mapToInt(l -> l.getValue().length()).max().orElse(10) + 2;
        int posWidth = 4;

        lexemeTypeWidth += 2;
        lexemeCategoryWidth += 2;
        valueWidth += 2;

        String header = String.format("%-" + lexemeCategoryWidth + "s| %-" + lexemeTypeWidth + "s| %-" + valueWidth + "s| %-" + posWidth + "s",
                "Категория лексемы", "Тип лексемы", "Значение", "Позиция");

        System.out.println(header);

        for (Lexeme lexeme : lexemes) {
            String row = String.format("%-" + lexemeCategoryWidth + "s| %-" + lexemeTypeWidth + "s| %-" + valueWidth + "s| %-" + posWidth + "s",
                    lexeme.getLexemeCategory(), lexeme.getLexemeType(), lexeme.getValue(), lexeme.getPos());
            System.out.println(row);
        }
    }
}
