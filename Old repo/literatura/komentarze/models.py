from django.db import models

# Create your models here.

class Dochody(models.Model):
	tytul     = models.CharField(max_length=30)
	wartosc   = models.IntegerField()
	data      =	models.DateField()
	stalosc   = models.IntegerField()
	kategoria = models.CharField(max_length=30)
class Wydatki(models.Model):
	tytul     = models.CharField(max_length=30)
	wartosc   = models.IntegerField()
	data      =	models.DateField()
	stalosc   = models.IntegerField()