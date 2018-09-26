package com.dsc.cs.androidpracticals;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.TextView;

public class MenuShowSelectedText extends AppCompatActivity {

    TextView textView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu_show_slected_text);

        textView = findViewById(R.id.menu_selected_text);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater menuInflater = getMenuInflater();
        menuInflater.inflate(R.menu.menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case R.id.menu_item_1:
                textView.setText(R.string.menu_item_1);
                break;
            case R.id.menu_item_2:
                textView.setText(R.string.menu_item_2);
                break;
            case R.id.menu_item_3:
                textView.setText(R.string.menu_item_3);
                break;
            case R.id.menu_item_4:
                textView.setText(R.string.menu_item_4);
                break;
            case R.id.menu_item_5:
                textView.setText(R.string.menu_item_5);
                break;
        }
        return super.onOptionsItemSelected(item);
    }
}
