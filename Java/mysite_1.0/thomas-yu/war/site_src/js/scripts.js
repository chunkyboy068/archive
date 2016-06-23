$(document).ready(function(){
  $("#expander").click(function(){
    $("#aboutmedesc").slideToggle("fast");
  });
});

$(document).ready(function(){
  $("#expander2").click(function(){
    $("#aboutsitedesc").slideToggle("fast");
  });
});

function mailtoAlert(){
	alert("Your default email program should open after clicking OK.");
}

function notHere(){
	alert("Thanks for your interest. Unfortunately, this page has not yet been created.  Please check back again later.
		If you don't want to wait, please use the contact page to contact me and I will be more than happy to send
		you anything you need.");
}