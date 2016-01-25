from django.conf.urls import patterns, include, url

from django.contrib import admin
import komentarze.views
admin.autodiscover()

urlpatterns = patterns('',

    url(r'^admin', include(admin.site.urls)),
    #url(r'^$',komentarze.views.ListElemViewDoch.as_view(), name='lst'),
    #url(r'^$',komentarze.views.ListElemViewWyd.as_view(), name='lst'),
    #url(r'^(?P<pk>\d+)/$',komentarze.views.ItemViewDoch.as_view(), name='detail'),
    #url(r'^(?P<pk>\d+)/$',komentarze.views.ItemViewWyd.as_view(), name='detail'),
    url(r'^login',komentarze.views.login, name='logowanie'),
    url(r'^auth',komentarze.views.auth_view, name='auth'),
    url(r'^logout',komentarze.views.logout, name='logout'),
    url(r'^loggedin',komentarze.views.loggedin, name='loggedin'),
    url(r'^invalid',komentarze.views.invalid_login, name='invalid'),
    #url(r'^dochody',komentarze.views.dochody, name='dochody'),
    #url(r'^wydatki',komentarze.views.wydatki, name='wydatki'),
    url(r'^dochody',komentarze.views.formularzDoch, name='dochody'),
    url(r'^wydatki',komentarze.views.formularzWyd, name='wydatki'),
    #url(r'^zestawienie',komentarze.views.zestawienie, name='zestawienie'),
    url(r'^zestawienie',komentarze.views.Zestawka, name='zestawka'),
    url(r'^zestawieniew',komentarze.views.Zestawka, name='zestawkaw'),
    #url(r'^edycja/(\d+)/',komentarze.views.EdytkaD, name='edycja dochodow'),
    url(r'^edycjaw',komentarze.views.EdytkaW, name='edycja wydatkow'),  
    url(r'^edycja', komentarze.views.EdytkaD, name='edytka dochodow'),  
    #url(r'^edycja', komentarze.views.EdytkaD, name='edytka dochodow'),
    url(r'^edytowanie',komentarze.views.Edytor, name='edytowanie'),
    url(r'^edit1',komentarze.views.Edit_doh, name='edit1'),      
    url(r'^edit2',komentarze.views.Edit_wyd, name='edit2'), 
    url(r'^edyt1',komentarze.views.Edyt_doh, name='edyt1'),    
    url(r'^edyt2',komentarze.views.Edyt_wyd, name='edyt2'),   
    url(r'^del1',komentarze.views.del_doh, name='del1'),  
    url(r'^del2',komentarze.views.del_wyd, name='del2'),   
    url(r'^bazowa',komentarze.views.baza, name='bazowa'),
)
