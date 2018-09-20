package com.dsc.cs.androidpracticals;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class ExplictIntentSecondActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_explict_intent_second);

        ((TextView)findViewById(R.id.received_explicit_intent_data)).
                setText(getIntent().getStringExtra("data"));

    }
}
