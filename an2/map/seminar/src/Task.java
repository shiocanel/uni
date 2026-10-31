import java.util.Objects;

public abstract class Task{
    private String taskID;
    private String description;

    public Task(String taskID, String description) {
        this.taskID = taskID;
        this.description = description;
    }

    public String getTaskID() { return taskID; }
    public String getDescription() { return description; }

    public void setTaskID(String taskID) {
        this.taskID = taskID;
    }
    public void setDescription(String description) {
        this.description = description;
    }

    public abstract void execute();

    public String toString(){
        return "|taskID=" + taskID + "|description=" + description;
    }

    public boolean equals(Object o){
        if(o instanceof Task){
            Task task = (Task)o;
            return task.taskID.equals(this.taskID);
        }
        return false;
    }

    public int hashCode(){
        return Objects.hash(taskID, description);
    }
}