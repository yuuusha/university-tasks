import java.util.Random;

public class ExponentialRandomGenerator { // Генератор случайной величины из экспоненциального распределения
    public static double generate(double lambda) {
        Random random = new Random();
        return -Math.log(random.nextDouble()) / lambda;
    }
}
