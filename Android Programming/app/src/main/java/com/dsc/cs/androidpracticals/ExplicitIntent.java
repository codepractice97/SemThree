package com.dsc.cs.androidpracticals;

import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class ExplicitIntent extends AppCompatActivity {

    Context context = this;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_explicit_intent);

        final EditText editText = findViewById(R.id.explicit_intent_data);
        Button button = findViewById(R.id.explicit_send_bt);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(context, ExplictIntentSecondActivity.class);
                intent.putExtra("data", editText.getText().toString());
                context.startActivity(intent);
            }
        });
    }
}
