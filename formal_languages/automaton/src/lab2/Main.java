package lab2;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {

    public static void main(String[] args) {

        String filePath = "src/lab2/program.txt";

        String program;
        try {
            program = Files.readString(Path.of(filePath));
        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла: " + e.getMessage());
            return;
        }

        SyntaxAnalyzer analyzer = new SyntaxAnalyzer();
        boolean res = analyzer.start(program);
        if (res) {
            System.out.println("Синтаксический анализ прошел успешно");
        }

    }
}
