<?hh // strict

namespace Rime\ActionDispatch\Session\Random;

class Randval implements \Rime\ActionDispatch\Session\Implementation\RandvalInterface
{

  protected Phpfunc $phpfunc;
  
  
  public function __construct($phpfunc)
  {
    $this->phpfunc = $phpfunc;
  }
  
  public function generate(): ?string
  {
    $bytes = 32;
  
    if ($this->phpfunc->extension_loaded('openssl')) 
    {
      return $this->phpfunc->openssl_random_pseudo_bytes($bytes);
    }
  
    if ($this->phpfunc->extension_loaded('mcrypt')) 
    {
      return $this->phpfunc->mcrypt_create_iv($bytes, MCRYPT_DEV_URANDOM);
    }
  
    $message = "Cannot generate cryptographically secure random values. "
    . "Please install extension 'openssl' or 'mcrypt', or use "
    . "another cryptographically secure implementation.";
    
    throw new \Rime\ActionDispatch\Session\Exception\Exception($message);
  }
}
