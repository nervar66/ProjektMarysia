package pl.pcz.icis.budzetdomowy;


import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;


import java.util.Locale;

import static android.app.PendingIntent.getActivity;

/**
 * Created by Nefalem on 2015-04-11.
 */

public class edytuj extends Activity {
    SQLiteDatabase db;
    String tabela1 = "Dochody";
    String tabela2 = "Wydatki";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.edytuj);
        /*if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.action_bar_container, new PlaceholderFragment())
                    .commit();
        }*/
        db=openOrCreateDatabase("Baza",MODE_PRIVATE, null);
    }

    public void tableClean1(View v){tableClean(v, true);}
    public void tableClean2(View v){tableClean(v, false);}

    public void tableClean(View v, boolean wyb)//dochody=true wydatki=false
    {
        String tabela="";
        if(wyb){
            Toast.makeText(getApplicationContext(), " Wyczyszczono dochody ", Toast.LENGTH_LONG).show();
            tabela=tabela1;
        }
        else
        {
            Toast.makeText(getApplicationContext(), " Wyczyszczono wydatki ", Toast.LENGTH_LONG).show();
            tabela=tabela2;
        }

        db.execSQL("DELETE FROM '"+tabela+"';");
        db.execSQL("DROP TABLE '" + tabela + "';");
    }

    public void tableEdit1(View v) throws ParseException { tableEdit(v, true);}//edycja dochodï¿½w
    public void tableEdit2(View v) throws ParseException { tableEdit(v, false);}//edycja wydatkï¿½w

    public void tableEdit(View v, final boolean rodz_bilansow) throws ParseException {
        String tabela="";
        if(rodz_bilansow)
        {
            tabela=tabela1;
        }
        else
        {
            tabela=tabela2;
        }
        Cursor c=db.rawQuery("SELECT * from '"+tabela+"'", null);
        int count= c.getCount();
        c.moveToFirst();
        TableLayout tableLayout = new TableLayout(getApplicationContext());
        tableLayout.setVerticalScrollBarEnabled(true);

        TableRow tableRow;
        TextView textView,textView1,textView2;
        Button button1;
        tableRow = new TableRow(getApplicationContext());
        textView=new TextView(getApplicationContext());
        if(rodz_bilansow)
        {
            textView.setText("Nazwa dochodu");
        }
        else
        {
            textView.setText("Nazwa wydatku");
        }
        textView.setTextColor(Color.BLUE);
        textView.setTypeface(null, Typeface.BOLD);
        textView.setPadding(20, 20, 20, 20);
        tableRow.addView(textView);

        //guziki edycj
        Button[] guziki = new Button[count];

        tableLayout.addView(tableRow);
        tableLayout.setBackgroundColor(Color.rgb(244, 196, 48));
        for (Integer j = 0; j < count; j++)
        {
            tableRow = new TableRow(getApplicationContext());
            textView1 = new TextView(getApplicationContext());
            textView1.setText(c.getString(c.getColumnIndex("title")));

            textView2 = new TextView(getApplicationContext());
            textView2.setText(c.getString(c.getColumnIndex("id")));
            int i=Integer.parseInt(textView2.getText().toString());

            guziki[j] = new Button(this);

            button1 =  guziki[j];
            button1.setPadding(20, 20, 20, 20);

            button1.setText(" Edycja ");
            button1.setTextColor(Color.rgb(70, 130, 180));
            textView1.setTextColor(Color.MAGENTA);
            textView2.setTextColor(Color.YELLOW);

            final Integer finalJ = i;
            final String tab = tabela;
            button1.setOnClickListener(new View.OnClickListener() {
                public void onClick(View v) {
                    try {
                        EditPosition(finalJ,rodz_bilansow,tab);
                    } catch (ParseException e) {
                        e.printStackTrace();
                    }
                }
            });

            textView1.setPadding(20, 20, 20, 20);
            textView2.setPadding(20, 20, 20, 20);

            tableRow.addView(textView2);
            tableRow.addView(textView1);
            tableRow.addView(button1);
            //tableRow.addView(button2);

            tableLayout.addView(tableRow);
            c.moveToNext() ;
        }

        setContentView(tableLayout);
        //db.close();

        //db.execSQL("DELETE FROM Dochody;");
    }

    public void EditPosition(Integer i, final boolean rodz_bil, String tablica) throws ParseException {

        String Indeks_wiersza_do_edycji = String.valueOf(i);

        TextView tytul, wartosc, data;
        CheckBox status;
        Spinner category=null;

        Cursor c = db.rawQuery("SELECT * from '"+tablica+"' WHERE id=" + Indeks_wiersza_do_edycji + "", null);
        c.moveToFirst();

        tytul = new TextView(getApplicationContext());
        tytul.setText(c.getString(c.getColumnIndex("title")));

        //Konwersja
        String strdate = c.getString(c.getColumnIndex("date"));
        String currentPattern = "EEE MMM dd kk:mm:ss z yyyy";
        SimpleDateFormat sdf = new SimpleDateFormat(currentPattern, Locale.ENGLISH);

        Date dt = sdf.parse(strdate); // new date is constructed
        System.out.println(dt);

        String newPattern = "dd-MM-yyyy";   // new pattern is defined
        sdf.applyPattern(newPattern);        // the same is applied
        String new_strdate = sdf.format(dt); // on the date object

        data = new TextView(getApplicationContext());
        data.setText(new_strdate);// resulting new string form of date
        //

        wartosc = new TextView(getApplicationContext());
        wartosc.setText(c.getString(c.getColumnIndex("value")));

        status = new CheckBox(getApplicationContext());
        status.setChecked(true);
        TextView Czek = new TextView(getApplicationContext());
        Czek.setText(c.getString(c.getColumnIndex("status")));

        if(Czek.getText().toString().equals("zmienny"))
        {
            status.setChecked(false);
        }

        if(rodz_bil)
        {
            category = new Spinner(getApplicationContext());
            category.setSelection(c.getColumnIndex("category"));
        }
        //

        TableLayout tableLayout = new TableLayout(getApplicationContext());
        tableLayout.setVerticalScrollBarEnabled(true);
        tableLayout.setBackgroundColor(Color.rgb(244, 196, 48));

        TextView[] obiekty1 = new TextView[]{tytul, data, wartosc};
        String[]   obiekty3 = new String[]{"Nazwa","Data","Wartosc","Status","Kategoria"};

        EditText[] edytka = new EditText[3];

        TableRow tableRow;
        for(int k=0;k<3;k++)
        {
            edytka[k]=new EditText(getApplicationContext());
            tableRow = new TableRow(getApplicationContext());
            TextView str = new TextView(getApplicationContext());
            str.setText(obiekty3[k]);
            str.setTextColor(Color.BLACK);
            str.setTypeface(null, Typeface.BOLD);
            str.setPadding(20, 20, 20, 20);
            tableRow.addView(str);//dodanie wiersza z tekstem

            edytka[k].setTextColor(Color.MAGENTA);
            edytka[k].setPadding(20, 20, 20, 20);
            edytka[k].setText(obiekty1[k].getText());
            
            tableRow.addView(edytka[k]);//dodanie teksta z informacja
            tableLayout.addView(tableRow);
        }
        ///////////
        tableRow = new TableRow(getApplicationContext());
        TextView str = new TextView(getApplicationContext());
        str.setText(obiekty3[3]);
        str.setTextColor(Color.BLACK);
        str.setTypeface(null, Typeface.BOLD);
        str.setPadding(20, 20, 20, 20);
        tableRow.addView(str);


        final CheckBox CHECK1,CHECK2;
        CHECK1=new CheckBox(getApplicationContext());
        CHECK2=new CheckBox(getApplicationContext());
        CHECK1.setTextColor(Color.MAGENTA);
        CHECK2.setTextColor(Color.MAGENTA);
        CHECK1.setPadding(20, 20, 20, 20);
        CHECK2.setPadding(20, 20, 20, 20);
        CHECK1.setText("Sta³y");
        CHECK2.setText("Czy chwilowy");

        if(status.isChecked())
        {
            CHECK1.setChecked(true);
        }
        else
        {
            CHECK2.setChecked(true);
        }

        tableRow.addView(CHECK1);
        tableRow.addView(CHECK2);
        tableLayout.addView(tableRow);
        ///////////

        final Spinner SPIN = new Spinner(getApplicationContext());
        if(rodz_bil)
        {
            tableRow = new TableRow(getApplicationContext());
            TextView str2 = new TextView(getApplicationContext());
            str2.setText(obiekty3[4]);
            str2.setTextColor(Color.BLACK);
            str2.setTypeface(null, Typeface.BOLD);
            str2.setPadding(20, 20, 20, 20);
            tableRow.addView(str2);

            ///spiner
            /*
            sort = (Spinner) getActivity().findViewById(R.id.spinner2);
            strings = getActivity().getResources().getStringArray(R.array.sorting_items);
            SpinnerSortAdapter sAdapter = new SpinnerSortAdapter(getActivity(),
                    android.R.layout.simple_spinner_item, strings);
            sAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            sort.setAdapter(sAdapter);
            sort.setOnItemSelectedListener(new MyOnItemSelectedListener());
            */
            //
            String[] items = getResources().getStringArray(R.array.spinka);
            MyArrayAdapter adapter = new MyArrayAdapter(this, android.R.layout.simple_spinner_item, items);


            //String[] items = getResources().getStringArray(R.array.spinka);

            //MyArrayAdapter<CharSequence> adapter = new MyArrayAdapter(this, android.R.layout.simple_spinner_item, items);
            //MyArrayAdapter adapter = new MyArrayAdapter(this, R.array.spinka, items);
            //MyArrayAdapter adapter = new MyArrayAdapter(this, R.array.spinka, android.R.layout.simple_spinner_item);
            adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            SPIN.setAdapter(adapter);
            //kolor

            //SPIN.setBackgroundResource(R.drawabl e.ready);

            tableRow.addView(SPIN);

            ///
            tableLayout.addView(tableRow);
        }

         /////////////////////
        tableRow = new TableRow(getApplicationContext());

        Button button_edytcji,button_usuwania;

        button_edytcji =  new Button(this);
        button_edytcji.setPadding(20, 20, 20, 20);

        button_edytcji.setText(" Zapisz zmiany ");
        button_edytcji.setTextColor(Color.rgb(70, 130, 180));

        final EditText[] finalJ = edytka;
        final String index = Indeks_wiersza_do_edycji;
        final String tab = tablica;
        final boolean wyb = rodz_bil;

        button_edytcji.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                try {
                    Zapisz_edycje(finalJ,index,tab,wyb,CHECK1,CHECK2,SPIN);
                } catch (ParseException e) {
                    e.printStackTrace();
                }
            }

            private void Zapisz_edycje(EditText[] finalJ, String i, String tablica_do_edycji, boolean wybor,CheckBox a,CheckBox b,Spinner c) throws ParseException {
                // konwersja ze stringa na date.
                SimpleDateFormat dt = new SimpleDateFormat("dd-MM-yyyy");
                Date data = dt.parse(finalJ[1].getText().toString());
                //konwersja ze stringa na inta.
                int var=Integer.parseInt(finalJ[2].getText().toString());
                //Sta³y czy zmienny status==true sta³y ==false zmienny
                String stability=null;
                if(CHECK1.isChecked())
                    stability="sta³y";
                if(CHECK2.isChecked())
                    stability = "zmienny";
                //
                if(wybor)
                {
                    String kat=SPIN.getSelectedItem().toString();
                    db.execSQL("UPDATE '"+tablica_do_edycji+"' SET category='"+kat+"' WHERE id='"+i+"';");
                }
                //
                db.execSQL("UPDATE '"+tablica_do_edycji+"' SET title='"+finalJ[0].getText().toString()+"' WHERE id='"+i+"';");
                db.execSQL("UPDATE '"+tablica_do_edycji+"' SET date='"+data+"' WHERE id='"+i+"';");
                db.execSQL("UPDATE '"+tablica_do_edycji+"' SET value='"+var+"' WHERE id='"+i+"';");
                db.execSQL("UPDATE '"+tablica_do_edycji+"' SET status='"+stability+"' WHERE id='" + i + "';");

                Toast.makeText(getApplicationContext(), ""+finalJ[0].getText().toString()+" zedytownao ", Toast.LENGTH_LONG).show();
            }
        });
        tableRow.addView(button_edytcji);

        button_usuwania =  new Button(this);
        button_usuwania.setPadding(20, 20, 20, 20);

        button_usuwania.setText(" UsuÅ„ pozycjÄ™ ");
        button_usuwania.setTextColor(Color.rgb(70, 130, 180));

        button_usuwania.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                try {
                    Usun_pozycje(finalJ, index, tab);
                } catch (ParseException e) {
                    e.printStackTrace();
                }
            }

            private void Usun_pozycje(EditText[] finalJ, String i, String tablica_do_edycji) throws ParseException {

                db.execSQL("DELETE FROM '"+tablica_do_edycji+"' WHERE id='" + i + "';");
                Toast.makeText(getApplicationContext(), "" + finalJ[0].getText().toString() + " usuniï¿½to ", Toast.LENGTH_LONG).show();
            }
        });
        tableRow.addView(button_usuwania);//

        tableLayout.addView(tableRow);
        setContentView(tableLayout);

        //db.execSQL("DELETE FROM Dochody Where id="+Indeks_wiersza_do_edycji+";");
        Toast.makeText(getApplicationContext(), ""+tytul.getText().toString()+" "+Indeks_wiersza_do_edycji+" ", Toast.LENGTH_LONG).show();
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
            View rootView = inflater.inflate(R.layout.edytuj, action_bar_container, false);
            return rootView;
        }
    }
}
