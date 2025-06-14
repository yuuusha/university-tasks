import java.util.ArrayList;
import java.util.List;

public class QueuingSystem {

    // Задаем начальные параметры
    static double curTime = 0;
    static double lambda = 0.5;
    static double mu = 0.6;

    // Максимальное число требований, которые можно взять - B
    static int maxRequirements = 3;

    // Счетчик для потерянных требований
    static int missedRequirements = 0;

    // Определяет занятость прибора
    static boolean busy = false;

    // Очередь для хранения созданных, но не исполненных требований и очередь для хранения исполненных требований
    static List<Requirement> queueActual = new ArrayList<>();
    static List<Requirement> queueFinished = new ArrayList<>();


    // Временная очередь, в которую будут помещаться 0 < k <= B выбранных требований
    static List<Requirement> queueTemp = new ArrayList<>();

    static Requirement curRequirement;

    // Моменты времени для создания следующего требования и обработки следующего требования
    static double creatingRequirementNextTime = 0;
    static double serviceRequirementNextTime = 0;

    // Массив, в который будут записываться количества текущих требований в системе
    static int[] arrayForNumsRequirement = new int[100];

    public static void main(String[] args) {
        curTime = 0;

        //int sumRequirements = 0;
        int i = 0;

        // Ограничим до 1000 исполненных требований
        while (queueFinished.size() < 100000) {
            createRequirement(); // Создаем требование, если это возможно
            getFromActual(); // Извлекаем k требований во временную очередь, если не заняты
            serviceRequirement(); // Обслуживаем взятые требования
            changeTime(); // Переводим время на следующий ближайший момент

            int numsRequirements = getNumActualRequirements(); // Считаем количество находящихся в системе требований
            //sumRequirements += numsRequirements;
            arrayForNumsRequirement[numsRequirements] += 1;
            i++;
        }

//        for (Requirement r : queueFinished) {
//            System.out.println("create: " + r.creatingTime);
//            System.out.println("serviceStart: " + r.startServiceTime);
//            System.out.println("serviceEnd: " + r.endServiceTime);
//            System.out.println();
//        }

        double sumTime = 0;
        for (Requirement r : queueFinished) {
            sumTime += r.timeSpentSystem;
        }
        double expectedValueTime = sumTime / queueFinished.size();
        System.out.println("Оценка матожидания времени нахождения требования в системе: " + expectedValueTime);

        int sumRequirements = 0;
        for (int j = 0; j < arrayForNumsRequirement.length; j++) {
            sumRequirements += j * arrayForNumsRequirement[j];
        }

        double expectedValueNumRequirements = (double) sumRequirements / i;
        System.out.println("Оценка матожидания числа требований в системе в момент времени: " + expectedValueNumRequirements);

//        double expectedValueNumRequirements = (double) sumRequirements / i;
//        System.out.println("Оценка матожидания числа требований в системе в момент времени: " + expectedValueNumRequirements);

        double probabilityMissed = (double) missedRequirements / (queueFinished.size() + missedRequirements);
        System.out.println("Вероятность потери требования: " + probabilityMissed);

    }

    public static void createRequirement() {
        // Если пришло время, создаем требование
        if (curTime >= creatingRequirementNextTime) {
            Requirement r = new Requirement(curTime);
            queueActual.add(r);
            creatingRequirementNextTime = curTime + ExponentialRandomGenerator.generate(lambda); // Определяем время до следующего создания требования
        }
    }

    public static void serviceRequirement() {
        if (busy) {
            // Если пришло время, заканчиваем обработку требования
            if (curTime >= serviceRequirementNextTime) {
                curRequirement.endServiceTime = curTime;
                curRequirement.timeSpentSystem = curRequirement.endServiceTime - curRequirement.creatingTime;
                queueFinished.add(new Requirement(curRequirement));
                busy = false;
                serviceRequirementNextTime = Double.POSITIVE_INFINITY; // Пока что обрабатывать нечего, так что переводим время на момент создания следующего требования
                serviceRequirement(); // Обрабатываем еще, если есть что обрабатывать
            }
        }
        else if (!queueTemp.isEmpty()) { // Если очередь на обработку не пуста
            curRequirement = new Requirement(queueTemp.removeFirst()); // Извлекаем на обработку новое требование
            curRequirement.startServiceTime = curTime;
            serviceRequirementNextTime = curTime + ExponentialRandomGenerator.generate(mu); // Задаем момент конца обработки данного требования
            busy = true;
        }
    }

    public static void getFromActual() {
        // Если не заняты, извлекаем из основной очереди k требований
        if (!busy) {
            if (!queueActual.isEmpty()) {
                int count = Math.min(maxRequirements, queueActual.size()); // k
                for (int i = 0; i < count; i++) {
                    queueTemp.add(queueActual.removeFirst());
                }
                missedRequirements += queueActual.size(); // Оставшиеся требования теряем
                queueActual.clear();
            }
        }
    }

    public static void changeTime() {
        // Переводим время на следующий ближайший момент
        curTime = Math.min(creatingRequirementNextTime, serviceRequirementNextTime);
    }

    // Получаем текущее число требований в системе - те, что находятся в очереди на ожидании обработки; те, что находятся в очереди на обработку и то требование, что обрабатывается в данный момент
    public static int getNumActualRequirements() {
        return queueActual.size() + queueTemp.size() + (busy ? 1 : 0);
    }
}