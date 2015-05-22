<?hh // strict

namespace Rime\ActionDispatch\Session\Implementation;

interface SegmentInterface
{  
  public function get(string $key, mixed $alt = null): mixed;
  public function set(string $key, mixed $val): void;
  public function clear(): void;
  public function setFlash(?string $key, ?mixed $val): void;
  public function getFlash(?string $key, $alt = null): mixed;
  public function clearFlash(): void;
  public function getFlashNext(string $key, mixed $alt = null): mixed;
  public function setFlashNow(string $key, mixed $val): void;
  public function clearFlashNow(): void;
  public function keepFlash(): void;
}
