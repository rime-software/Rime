<?hh // strict

namespace Rime\System\Framework;

class Loader
{
  
  public function file(string $file, Map $config = Map{}): void
  {
    $extension = $config->contains('extension') ? $config->contains('extension') : '.hh';
    try
    {
      if(!$config->contains('customPath') && $config->get('customPath') == false)
        include_once BASE_PATH.'/'.$file.$extension;
      else
        include_once $file.$extension;
    }
    catch (Exception $e)
    {
      if($config->contains('silent') && $config->get('silent') == false)
        throw new Exception('Unable to load file: '.$file);
    }
  }

}