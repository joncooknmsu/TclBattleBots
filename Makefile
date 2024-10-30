
tar:
	(cd ..;  tar cvf /home/others1/jcook/public_html/battlebots.tar battlebots/playbots battlebots/mostlyrandom battlebots/README battlebots/random.c;  cd battlebots)

srctar:
	(cd ..;  tar cvf tb.tar battlebots/; cd battlebots)
	mv ../tb.tar .

