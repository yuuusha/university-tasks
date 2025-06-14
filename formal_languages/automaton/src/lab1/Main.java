package lab1;

import java.util.List;

public class Main {

    public static void main(String[] args) {

        String program = "do a = a + 1 loop until a <= 10";

        LexicalAnalyzer lexicalAnalyzer = new LexicalAnalyzer();
        lexicalAnalyzer.start(program);

        List<Lexeme> lexemes = lexicalAnalyzer.getLexemes();

        Lexeme.printLexemeTable(lexemes);


    }

}
