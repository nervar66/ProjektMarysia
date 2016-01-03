package pl.pcz.icis.budzetdomowy;

import android.app.Activity;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Toast;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by Nefalem on 2015-04-11.
 */

public class wydatki extends Activity{
    SQLiteDatabase db;
    EditText Text1,Text2,Text3;
    CheckBox check1, check2;
    String tyt,stat;
    int war;
    Date data;
    String data_str;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.wydatki);
        /*if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.action_bar_container, new PlaceholderFragment())
                    .commit();
        }*/
        Text1=(EditText)findViewById(R.id.editText);//tytu�
        Text2=(EditText)findViewById(R.id.editText2);//data
        Text3=(EditText)findViewById(R.id.editText3);//wartosc
        check1=(CheckBox)findViewById(R.id.checkBox);//sta�y wydatek
        check2=(CheckBox)findViewById(R.id.checkBox2);//chwilowy
        db=openOrCreateDatabase("Baza",MODE_PRIVATE, null);
        db.execSQL("CREATE TABLE IF NOT EXISTS Wydatki(id INTEGER PRIMARY KEY, title VARCHAR, date DATE, value INT, status VARCHAR);");
    }

    public void onBatonClick(View v) throws ParseException {
        tyt=Text1.getText().toString();
        //data
        data_str = Text2.getText().toString();

        // konwersja ze stringa na date.
        SimpleDateFormat dt = new SimpleDateFormat("dd-MM-yyyy");
        data = dt.parse(data_str);
        //konwersja ze stringa na inta.
        war=Integer.parseInt(Text3.getText().toString());

        if(check1.isChecked())
            stat="stały";
        if(check2.isChecked())
            stat = "zmienny";
        db.execSQL("INSERT INTO  Wydatki VALUES(NULL,'"+tyt+"','"+data+"','"+war+"','"+stat+"');");
        Toast.makeText(getApplicationContext(), " " + tyt + " " + data + " " + war + " " + stat + " ", Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int itemId = item.getItemId();
        if (itemId == R.id.glowna) {
            startActivity (new Intent (this, main.class));
            return true;
        }
        if(itemId == R.id.dodusu1){
            startActivity (new Intent (this, dochody.class));
            return true;
        }
        if(itemId == R.id.dodusu2){
            startActivity (new Intent (this, wydatki.class));
            return true;
        }
        if(itemId == R.id.statystyki){
            startActivity (new Intent (this, pokaz.class));
            return true;
        }
        if(itemId == R.id.edytuj){
            startActivity (new Intent (this, edytuj.class));
            return true;
        }
        else{
            return super.onOptionsItemSelected(item);
        }
    }

    public static class PlaceholderFragment extends Fragment {

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup action_bar_container,
                                 Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.wydatki, action_bar_container, false);
            return rootView;
        }
    }
}
