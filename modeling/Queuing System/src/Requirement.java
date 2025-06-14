public class Requirement { // Класс для работы с объектами требований
    double creatingTime; // Время создания требования
    double startServiceTime; // Время начала обработки требования
    double endServiceTime; // Время конца обработки требования

    double timeSpentSystem; // Общее время нахождения требования в системе (endServiceTime - creatingTime)

    public Requirement(double creatingTime) {
        this.creatingTime = creatingTime;
        this.startServiceTime = -1;
        this.endServiceTime = -1;
        this.timeSpentSystem = -1;
    }

    public Requirement(Requirement requirement) {
        this.creatingTime = requirement.creatingTime;
        this.startServiceTime = requirement.startServiceTime;
        this.endServiceTime = requirement.endServiceTime;
        this.timeSpentSystem = requirement.timeSpentSystem;
    }
}
