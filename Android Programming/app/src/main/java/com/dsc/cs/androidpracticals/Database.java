package com.dsc.cs.androidpracticals;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import database.DBModel;
import database.SQLiteAdapter;

public class Database extends AppCompatActivity {

    SQLiteAdapter sqLiteAdapter;
    TextView textView;
    EditText editText;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_database);

        textView = findViewById(R.id.db_contents);
        editText = findViewById(R.id.database_input);

        sqLiteAdapter = new SQLiteAdapter(this);
    }

    public void addDB(View view){
        DBModel dbModel = new DBModel();
        dbModel.setContent(editText.getText().toString());
        sqLiteAdapter.insertName(dbModel);
        textView.setText(sqLiteAdapter.getDB());
    }

    public void removeDB(View view){
        sqLiteAdapter.deleteName(editText.getText().toString());
        textView.setText(sqLiteAdapter.getDB());
    }

    public void updateDB(View view){
        DBModel dbModel = new DBModel();
        dbModel.setContent(editText.getText().toString());
        sqLiteAdapter.updateLastEntry(dbModel);
        textView.setText(sqLiteAdapter.getDB());
    }
}
