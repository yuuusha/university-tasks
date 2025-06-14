package PutMessage;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ParamsPut {
    public Map<String, String> params;

    public ParamsPut(String[] args) {

        if (List.of(args).contains("<") && List.of(args).contains(">")) {
            if (!args[0].equals("-c")) {
                throw new RuntimeException("Первым должен быть контейнер");
            }

            for (int i = 0; i < args.length; i++) {
                if (args[i].equals("<")) {
                    args[i] = "-m";
                }
                if (args[i].equals(">")) {
                    args[i] = "-s";
                }
            }
        }

        Map<String, String> parameters = new HashMap<>();
        for (int i = 0; i < args.length; i++) {
            if (args[i].startsWith("-")) {
                if (i + 1 < args.length && !args[i + 1].startsWith("-")) {
                    parameters.put(args[i], args[i + 1]);
                    i++;
                } else {
                    parameters.put(args[i], null);
                }
            }
        }

        if (parameters.containsKey("-h") || parameters.containsKey("--help")) {
            System.out.println("Программа встраивает  сообщение  в  контейнер.\n" +
                    "-m и --message – путь к файлу, содержащему сообщение. Если не указан, то сообщение передаётся через стандартный поток ввода.\n" +
                    "-s и --stego  –  путь по которому нужно записать  стегоконтейнер,  Если не указан, то результат выводится в стандартный поток вывода.\n" +
                    "-c и --container – путь к файлу-контейнеру. Обязательный параметр!\n" +
                    "-h и --help – вывести справку о том, как использовать программу");
        }

        if (!parameters.containsKey("-c") && !parameters.containsKey("--container")) {
            throw new RuntimeException("Ошибка: Параметр -c (или --container) обязателен!");
        }

        if (!parameters.containsKey("-m") && !parameters.containsKey("--message")) {
            parameters.put("-m", "std");
        }
        if (!parameters.containsKey("-s") && !parameters.containsKey("--stego")) {
            parameters.put("-s", "std");
        }

        params = new HashMap<>(parameters);
    }

    public String getMessage() {
        if (params.containsKey("-message")) {
            return params.get("--message");
        }
        return params.get("-m");
    }

    public String getStego() {
        if (params.containsKey("--stego")) {
            return params.get("--stego");
        }
        return params.get("-s");
    }

    public String getContainer() {
        if (params.containsKey("--container")) {
            return params.get("--container ");
        }
        return params.get("-c");
    }
}
