package database;

public class DBModel {

    int key;
    String content;

    public int getKey(){
        return key;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content){
        this.content = content;
    }

    public void setKey(int key) {
        this.key = key;
    }

}