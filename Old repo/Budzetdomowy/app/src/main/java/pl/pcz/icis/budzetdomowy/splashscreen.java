package pl.pcz.icis.budzetdomowy;

import android.app.Activity;

/**
 * Created by Nefalem on 2015-04-03.
 */
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.os.Handler;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;

public class splashscreen extends Activity {
    //Set waktu lama splashscreen
    private static int splashInterval = 2000;
    SQLiteDatabase db;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(R.layout.splashscreen);
        db=openOrCreateDatabase("Baza",MODE_PRIVATE, null);
        db.execSQL("CREATE TABLE IF NOT EXISTS Wydatki(id INTEGER PRIMARY KEY, title VARCHAR, date DATE, value INT, status VARCHAR);");
        db.execSQL("CREATE TABLE IF NOT EXISTS Dochody(id INTEGER PRIMARY KEY, title VARCHAR,date DATE,value INT,status VARCHAR,category VARCHAR);");
        new Handler().postDelayed(new Runnable() {


            @Override
            public void run() {
                // TODO Auto-generated method stub
                Intent i = new Intent(splashscreen.this, main.class);
                startActivity(i);
                this.finish();
            }

            private void finish() {
                // TODO Auto-generated method stub

            }
        }, splashInterval);

    };
}
