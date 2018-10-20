package database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class SQLiteAdapter extends SQLiteOpenHelper {

    private final static int DATABASE_VERSION = 1;
    private final static String TABLE_NAME = "names";
    private final static String DATABASE_NAME = "myDB";

    private static final String key_id = "_id";
    private static final String key_content = "content";

    public SQLiteAdapter(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        String create_table_query = "CREATE TABLE " + TABLE_NAME + " (" +
                key_id + " INTEGER PRIMARY KEY, " + key_content + " TEXT );";
        sqLiteDatabase.execSQL(create_table_query);
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int oldVersion, int newVersion) {
        sqLiteDatabase.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(sqLiteDatabase);
    }

    public void insertName(DBModel dbModel){
        ContentValues contentValues = new ContentValues();
        contentValues.put(key_content, dbModel.getContent());
        SQLiteDatabase sqLiteDatabase = getWritableDatabase();
        sqLiteDatabase.insert(TABLE_NAME, null, contentValues);
        sqLiteDatabase.close();
    }

    public void updateLastEntry(DBModel dbModel){
        ContentValues contentValues = new ContentValues();
        contentValues.put(key_content, dbModel.getContent());
        SQLiteDatabase sqLiteDatabase = getWritableDatabase();
        Cursor cursor = sqLiteDatabase.query(TABLE_NAME, null, null, null,
                null, null, key_id +" DESC");
        cursor.moveToFirst();
        int pos = cursor.getInt(cursor.getColumnIndex(key_id));
        String []selectionArgs = { Integer.toString(pos) };
        sqLiteDatabase.update(TABLE_NAME, contentValues,
                key_id + " = ? ", selectionArgs);
        cursor.close();
        sqLiteDatabase.close();
    }

    public void deleteName(String name){
        SQLiteDatabase sqLiteDatabase = getWritableDatabase();
        sqLiteDatabase.execSQL("DELETE FROM " + TABLE_NAME + " WHERE " + key_content + "=\"" +
                name + "\";" );
        sqLiteDatabase.close();
    }

    public String getDB(){
        SQLiteDatabase sqLiteDatabase = getReadableDatabase();
        String data = "";
        Cursor cursor = sqLiteDatabase.rawQuery("SELECT " + key_content + " FROM " + TABLE_NAME, null);
        cursor.moveToFirst();
        while (!cursor.isAfterLast()){
            data += cursor.getString(cursor.getColumnIndex(key_content));
            data += "\n";
            cursor.moveToNext();
        }
        sqLiteDatabase.close();
        return data;
    }
}
