<?hh // strict

namespace Rime\ActionDispatch\Session\Segment;

class Segment implements \Rime\ActionDispatch\Session\Implementation\SegmentInterface
{
  protected Session $session;
  protected string $name;
  
  public function __construct(\Rime\ActionDispatch\Session\User\Session $session, string $name)
  {
    $this->session = $session;
    $this->name = $name;
  }
  
  public function get(string $key, $alt = null): mixed
  {
    $this->resumeSession();
    return isset($_SESSION[$this->name][$key])
      ? $_SESSION[$this->name][$key]
      : $alt;
  }
  
  public function set(string $key, mixed $val): void
  {
    $this->resumeOrStartSession();
    $_SESSION[$this->name][$key] = $val;
  }
  
  public function clear(): void
  {
    if ($this->resumeSession()) 
    {
      $_SESSION[$this->name] = array();
    }
  }
  
  public function setFlash(string $key, mixed $val): void
  {
    $this->resumeOrStartSession();
    $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name][$key] = $val;
  }
  
  public function getFlash(string $key, mixed $alt = null): mixed
  {
    $this->resumeSession();
    return isset($_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NOW][$this->name][$key])
      ? $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NOW][$this->name][$key]
      : $alt;
  }
  
  public function clearFlash(): void
  {
    if ($this->resumeSession()) 
    {
      $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name] = array();
    }
  }
  
  public function getFlashNext(string $key, mixed $alt = null): mixed
  {
    $this->resumeSession();
    return isset($_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name][$key])
      ? $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name][$key]
      : $alt;
  }
  
  public function setFlashNow(string $key, mixed $val): mixed
  {
    $this->resumeOrStartSession();
    $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NOW][$this->name][$key] = $val;
    $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name][$key] = $val;
  }
  
  public function clearFlashNow(): void
  {
    if ($this->resumeSession()) 
    {
      $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NOW][$this->name] = array();
      $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name] = array();
    }
  }
  
  public function keepFlash(): void
  {
    if ($this->resumeSession()) 
    {
      $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name] = array_merge(
        $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name],
        $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NOW][$this->name]
      );
    }
  }
  
  protected function resumeSession(): boolean
  {
    if ($this->session->isStarted() || $this->session->resume()) 
    {
      $this->load();
      return true;
    }
  
    return false;
  }
  
  protected function load(): void
  {
    if (! isset($_SESSION[$this->name])) 
    {
      $_SESSION[$this->name] = array();
    }
  
    if (! isset($_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NOW][$this->name])) 
    {
      $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NOW][$this->name] = array();
    }
  
    if (! isset($_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name])) 
    {
      $_SESSION[\Rime\ActionDispatch\Session\User\Session::FLASH_NEXT][$this->name] = array();
    }
  }
  
  protected function resumeOrStartSession(): void
  {
    if (! $this->resumeSession()) 
    {
      $this->session->start();
      $this->load();
    }
  }
}
