<?hh // strict

namespace Rime\ActionDispatch\Session\Factory;

class CsrfTokenFactory
{

  protected \Rime\ActionDispatch\Session\Implementation\RandvalInterface $randval;
  
  public function __construct(\Rime\ActionDispatch\Session\Implementation\RandvalInterface $randval)
  {
    $this->randval = $randval;
  }
  
  public function newInstance(\Rime\ActionDispatch\Session\User\Session $session): \Rime\ActionDispatch\Session\Csrf\CsrfToken
  {
    $segment = $session->getSegment('\Rime\ActionDispatch\Session\Csrf\CsrfToken');
    return new \Rime\ActionDispatch\Session\Csrf\CsrfToken($segment, $this->randval);
  }
}
