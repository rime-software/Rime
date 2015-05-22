<?hh //strict

$templateMap = array_map($view ==> TEMPLATE_PATH.'/'.$view,array(
  	'master' => 'master.hh',
  	'error' => 'error.hh',
  	'notfound' => '404.hh'
	)
);