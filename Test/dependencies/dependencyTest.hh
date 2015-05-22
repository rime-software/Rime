<?hh // strict

class dependencyTest extends PHPUnit_Framework_TestCase
{
  protected string $HHVM_VERSION;
  
  protected function setUp(): void
  {
    $this->HHVM_VERSION = defined('HHVM_VERSION') ? HHVM_VERSION : false;
  }
  
  public function testHipHopVirtualMachineVersion(): void
  {
    preg_match_all('!\d+!', $this->HHVM_VERSION, $matches);
    $current_version = (int)implode('', $matches[0]);
    
    $this->assertGreaterThanOrEqual(HHVM_MIN_VERSION, $current_version);
  }
}