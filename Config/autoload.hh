<?hh // strict

/************************************************************************************/
/* This file provides the default object-namespace loading in the following order:  */
/*  Rime Framework                                                                  */
/************************************************************************************/

/*************************************************************************/
/* Autoload the Rime Framework when it's namespaces are called.          */
/*************************************************************************/

spl_autoload_register( function($class){
  $file = BASE_PATH
    . implode( '', array_map( $fragment ==> "/$fragment", explode( '\\', $class ) ) )
    . '.hh';
  
  if(file_exists($file))
  {
    require_once $file;
  }
});