package pl.pcz.icis.budzetdomowy;

import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.ActionBar;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.os.Build;
import android.content.Intent;
import android.view.View.*;

public class main extends ActionBarActivity{

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    if (savedInstanceState == null) {
      getSupportFragmentManager().beginTransaction()
          .add(R.id.container, new PlaceholderFragment())
          .commit();
    }
  }

   public void onButtonClick(View v){
       startActivity (new Intent (this, dochody.class));
   }
    public void onButtonClick1(View v){
        startActivity (new Intent (this, wydatki.class));
    }
    public void onButtonClick2(View v){
        startActivity (new Intent (this, pokaz.class));
    }
    public void onButtonClick3(View v){
        startActivity (new Intent (this, edytuj.class));
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

  /**
   * A placeholder fragment containing a simple view.
   */
  public static class PlaceholderFragment extends Fragment {

    public PlaceholderFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
      View rootView = inflater.inflate(R.layout.fragment_main, container, false);
      return rootView;
    }
  }
}
