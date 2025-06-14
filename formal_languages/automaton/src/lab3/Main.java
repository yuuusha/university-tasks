package lab3;

import lab2.SyntaxAnalyzer;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {

    public static void main(String[] args) {

        String filePath = "src/lab3/program.txt";

        String program;
        try {
            program = Files.readString(Path.of(filePath));
        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла: " + e.getMessage());
            return;
        }

        SyntaxAnalyzerInnerCode analyzer = new SyntaxAnalyzerInnerCode();
        boolean res = analyzer.start(program);
        if (res) {
            System.out.println("Синтаксический анализ прошел успешно");
        }

        analyzer.getPostfixList().print();

    }
}
