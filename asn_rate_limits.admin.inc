<?php
/**
 * @file
 * Admin form to manage module settings
 *
 */

/**
 * Define the form for manage settings
 *
 */
function asn_rate_limits_form($form, &$form_state) {
  $config = config('asn_rate_limits.settings');

  $form['top'] = array(
    '#markup' => t('If a web crawler or even a person (except for logged
    in users) <u>exceeds all the limits during the time window</u> specified in the
    fields below, their IP address will be blocked <u>immediately without
    warning</u>. The requests and limits are checked on each cron run. In case
    an ASN is blocked during this regular check, all incoming requests are
    furtheron checked and IPs of the blocked ASN are immediately blocked.
    ASNs are automatically unblocked when they do not exceed the limits anymore
    during a regular check.'),
  );

  $url = url('admin/config/people/ip-blocking');
  $form['info'] = array(
    '#markup' => '<p>'. t('You can manage blocked IPs at  <a href="@url">this page</a>.', array('@url' => $url)) . '</p>',
  );

  $form['time_window'] = array(
    '#type' => 'number',
    '#title' => t('Time window in which below limits apply'),
    '#default_value' => $config->get('time_window'),
    '#min' => 1,
    '#max' => 180,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-180')),
    '#field_suffix' => 'minutes'
  );

  $form['ips_limit'] = array(
    '#type' => 'number',
    '#title' => t('Maximum allowed number of IPs per ASN'),
    '#default_value' => $config->get('ips_limit'),
    '#min' => 1,
    '#max' => 100,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-100')),
    '#field_suffix' => 'distinct IP addresses'
  );

  $form['hits_limit'] = array(
    '#type' => 'number',
    '#title' => t('Maximum allowed number of requests per IP or ASN'),
    '#default_value' => $config->get('hits_limit'),
    '#min' => 1,
    '#max' => 100,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-100')),
    '#field_suffix' => 'hits'
  );

  $form['time_limit'] = array(
    '#type' => 'number',
    '#title' => t('Maximum allowed execution time per IP or ASN'),
    '#default_value' => $config->get('time_limit'),
    '#min' => 1,
    '#max' => 100,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-100')),
    '#field_suffix' => 'seconds'
  );

  $form['server_load_limit'] = array(
    '#type' => 'number',
    '#title' => t('Maximum allowed current sever load'),
    '#default_value' => $config->get('server_load_limit'),
    '#min' => 1,
    '#max' => 100,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-100')),
    '#field_suffix' => '%'
  );

  $form['email_notification'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable email notification'),
    '#default_value' => $config->get('email_notification'),
    '#description' => t('Send a notification to the site email address when an ASN is blocked during an automated check in the cron run.'),
  );

  $form['unblock'] = array(
    '#type' => 'checkbox',
    '#title' => t('Unblock blocked IPs automatically after:') . '&nbsp;',
    '#default_value' => $config->get('unblock'),
    '#prefix' => '<div style="display:inline-flex;align-items:center">'
  );
  $form['unblock_after'] = array(
    '#type' => 'select',
    '#options' => array(
      900 => t('15 minutes'),
      3600 => t('60 minutes'),
      43200 => t('12 hours'),
      86400 => t('24 hours'),
      604800 => t('7 days'),
      2592000 => t('30 days'),
      31536000 => t('365 days'),
    ),
    '#default_value' => $config->get('unblock_after'),
    '#suffix' => '</div>',
    '#states' => array(
      'disabled' => array(
        ':input[name="unblock"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['maxmind_account_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Maxmind Account ID'),
    '#default_value' => $config->get('maxmind_account_id'),
  );

  $form['maxmind_license_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Maxmind License Key'),
    '#default_value' => $config->get('maxmind_license_key'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Implements hook_submit().
 */
function asn_rate_limits_form_submit($form, &$form_state) {
  $config = config('asn_rate_limits.settings');

  $config->set('time_window', (int) $form_state['values']['time_window']);
  $config->set('ips_limit', (int) $form_state['values']['ips_limit']);
  $config->set('hits_limit', (int) $form_state['values']['hits_limit']);
  $config->set('time_limit', (int) $form_state['values']['time_limit']);
  $config->set('server_load_limit', (int) $form_state['values']['server_load_limit']);
  $config->set('email_notification', (int) $form_state['values']['email_notification']);
  $config->set('unblock', (int) $form_state['values']['unblock']);
  $config->set('unblock_after', (int) $form_state['values']['unblock_after']);
  $config->set('maxmind_account_id', $form_state['values']['maxmind_account_id']);
  $config->set('maxmind_license_key', $form_state['values']['maxmind_license_key']);

  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
