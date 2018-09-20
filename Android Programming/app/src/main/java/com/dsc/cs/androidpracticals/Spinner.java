package com.dsc.cs.androidpracticals;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.TextView;

public class Spinner extends AppCompatActivity implements AdapterView.OnItemSelectedListener {

    android.widget.Spinner spinner;
    ImageView imageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_spinner);

        spinner = findViewById(R.id.image_spinner);
        imageView = findViewById(R.id.spinner_image_view);

        spinner.setOnItemSelectedListener(this);
    }

    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
        if (i == 0)
            imageView.setImageResource(R.drawable.india);
        else if (i == 1)
            imageView.setImageResource(R.drawable.china);
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {

    }
}
