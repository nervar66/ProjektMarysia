from django.conf.urls import patterns, include, url

from django.contrib import admin
import mysiteapp.views
admin.autodiscover()

urlpatterns = patterns('',

    url(r'^admin', include(admin.site.urls)),
    url(r'^login',mysiteapp.views.login, name='logowanie'),
    url(r'^auth',mysiteapp.views.auth_view, name='auth'),
    url(r'^logout',mysiteapp.views.logout, name='logout'),
    url(r'^loggedin',mysiteapp.views.loggedin, name='loggedin'),
    url(r'^invalid',mysiteapp.views.invalid_login, name='invalid'),
    url(r'^dochody',mysiteapp.views.formularzDoch, name='dochody'),
    url(r'^wydatki',mysiteapp.views.formularzWyd, name='wydatki'),
    url(r'^zestawienie',mysiteapp.views.Zestawka, name='zestawka'),
    url(r'^zestawieniew',mysiteapp.views.Zestawka, name='zestawkaw'),
    url(r'^edycjaw',mysiteapp.views.EdytkaW, name='edycja wydatkow'),  
    url(r'^edycja', mysiteapp.views.EdytkaD, name='edytka dochodow'),  
    url(r'^edytowanie',mysiteapp.views.Edytor, name='edytowanie'),
    url(r'^edit1',mysiteapp.views.Edit_doh, name='edit1'),      
    url(r'^edit2',mysiteapp.views.Edit_wyd, name='edit2'), 
    url(r'^edyt1',mysiteapp.views.Edyt_doh, name='edyt1'),    
    url(r'^edyt2',mysiteapp.views.Edyt_wyd, name='edyt2'),   
    url(r'^del1',mysiteapp.views.del_doh, name='del1'),  
    url(r'^del2',mysiteapp.views.del_wyd, name='del2'),   
    url(r'^bazowa',mysiteapp.views.baza, name='bazowa'),
)
