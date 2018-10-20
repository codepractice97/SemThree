package com.dsc.cs.androidpracticals;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    Button button[];
    final int button_id[] = {R.id.button1, R.id.button2, R.id.button3, R.id.button4,
            R.id.button5, R.id.button6, R.id.button7, R.id.button8, R.id.button9, R.id.button10};
    final Class activity_list[] = {HelloWorld.class, Lifecycle.class,
            ExplicitIntent.class, Login.class, ThreeBackground.class, Spinner.class,
            ImplicitIntent.class, MenuShowSelectedText.class, RadioGroup.class, Database.class };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = new Button[button_id.length];
        for (int i = 0; i < button_id.length; i++) {
            button[i] = findViewById(button_id[i]);
            button[i].setOnClickListener(this);
        }
    }

    @Override
    public void onClick(View view) {
        int id = view.getId();
        for (int i = 0; i < button_id.length; i++) {
            if (id == button_id[i]){
                Intent intent = new Intent(this, activity_list[i]);
                startActivity(intent);
                break;
            }
        }
    }
}
